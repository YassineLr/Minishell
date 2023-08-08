/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:49:26 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/08 21:47:01 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	heredoc_count2(t_list *list)
{
	int	count;
	int	prev_type;

	count = 0;
	prev_type = -1;
	while (list && list->token->type != PIPE)
	{
		if (list->token->type == HEREDOC)
		{
			if (!handle_heredoc(&list, prev_type))
				return (count);
			else
				count++;
		}
		else
		{
			if (!hc_handle_errors(prev_type, list->token->type))
				return (count);
		}
		prev_type = list->token->type;
		list = list->next;
	}
	return (count);
}

int	hc_handle_errors(int prev_type, int curr_type)
{
	if (curr_type == PIPE && (is_redir(prev_type) || prev_type == PIPE))
		return (0);
	else if (curr_type == RED_IN && is_redir_2(prev_type))
		return (0);
	else if (curr_type == RED_OUT && is_redir_2(prev_type))
		return (0);
	else if (curr_type == APPEND && is_redir_2(prev_type))
		return (0);
	return (1);
}

int	handle_heredoc(t_list **list, int prev_type)
{
	if (is_redir_2(prev_type) || is_quotes(prev_type))
		return (0);
	if ((*list)->next)
	{
		*list = (*list)->next;
		if ((*list)->next)
		{
			if (is_quotes((*list)->token->type))
				*list = (*list)->next;
		}
		if ((*list)->token->type != WORD)
			return (0);
	}
	else
		return (0);
	return (1);
}

int	heredoc_count(t_list *list)
{
	int	count;
	int	prev_type;

	count = 0;
	prev_type = -1;
	while (list)
	{
		if (list->token->type == HEREDOC)
		{
			if (!handle_heredoc(&list, prev_type))
				return (count);
			else
				count++;
		}
		else
		{
			if (!hc_handle_errors(prev_type, list->token->type))
				return (count);
		}
		prev_type = list->token->type;
		list = list->next;
	}
	return (count);
}

t_hdc	*init_hdc(int count)
{
	t_hdc	*hdc;

	hdc = malloc(sizeof(t_hdc));
	if (!hdc)
		return (0);
	hdc->count = count;
	hdc->fds = malloc(sizeof(int) * count);
	if (!hdc->fds)
		return (0);
	return (hdc);
}

int	heredoc_count3(t_list **list)
{
	int	count;
	int	prev_type;

	count = 0;
	prev_type = -1;
	while (*list && (*list)->token->type != PIPE)
	{
		if ((*list)->token->type == HEREDOC)
		{
			count = 1;
			if (!handle_heredoc(list, prev_type))
				return (count);
			else
				count = 1;
		}
		else if ((*list)->token->type == RED_IN)
			count = 0;			
		else
		{
			if (!hc_handle_errors(prev_type, (*list)->token->type))
				return (count);
		}
		prev_type = (*list)->token->type;
		*list = (*list)->next;
	}
	return (count);
}

int	count_ends(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count += heredoc_count3(&list);
		if (list && list->token->type == PIPE)
			list = list->next;
		else
			return (count);
	}
	return (count);
}

t_hdc	*here_doc(t_list *list, t_env *env)
{
	int		i;
	int		pid;
	int		expand;
	int		count_hdcs;
	int		count;
	int		**ends;
	t_hdc	*hdc;
	char	*hdoc_line;
	int		pipe_count;
	int		status;

	i = 0;
	expand = 1;
	pipe_count = count_ends(list);
	ends = malloc(sizeof(int *) * pipe_count);
	while (i < pipe_count)
	{
		ends[i] = malloc(sizeof(int) * 2);
		if (pipe(ends[i]) == -1)
			return (0);
		i++;
	}
	count_hdcs = heredoc_count(list);
	if (!count_hdcs)
		return (0);
	hdc = init_hdc(pipe_count);
	if (!hdc)
		return (0);
	pid = fork();
	g.in_hdoc = 1;
	if (!pid)
	{	
		i = 0;
		signal(SIGINT, ctrl_c_hdoc);
		while (i < pipe_count)
		{
			close(ends[i][0]);
			i++;
		}
		i = 0;
		while (list && count_hdcs > 0)
		{
			count = heredoc_count2(list);
			if (!count)
			{
				while (list && list->token->type != PIPE)
					list = list->next;
				if (list)
					list = list->next;
			}
			else
			{
				while (list && list->token && list->token->type != PIPE && count_hdcs > 0)
				{
					if (list->token->type == HEREDOC)
					{
						list = list->next;
						if (is_quotes(list->token->type))
						{
							expand = 0;
							list = list->next;
						}
						while (1)
						{
							if (!count || !count_hdcs)
								break ;
							hdoc_line = readline("> ");
							if (!hdoc_line)
								break ;
							if (ft_strcmp(hdoc_line, list->token->value))
							{
								if (count == 1)
								{
									if (expand == 0)
										ft_putendl_fd(hdoc_line, ends[i][1]);
									else
										heredoc_expand(hdoc_line, env, ends[i][1]);
								}
							}
							else
								break ;
							if (hdoc_line)
								free(hdoc_line);
						}
						if (count == 1)
							i++;
						if (hdoc_line)
							free(hdoc_line);
						count--;
						count_hdcs--;
					}
					else
						list = list->next;
				}
			}
		}
		i = 0;
		while (i < pipe_count)
		{
			close(ends[i][1]);
			i++;
		}
		exit(exitcode);
	}
	else
	{
		while(waitpid(-1, &status, 0) != -1)
			exit_status(status);
		i = 0;
		while (i < pipe_count)
		{
			close(ends[i][1]);
			i++;
		}
		i = 0;
		while (i < pipe_count)
		{
			hdc->fds[i] = ends[i][0];
			i++;
		}
	}
	g.in_hdoc = 0;
	return (hdc);
}
