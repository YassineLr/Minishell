/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:49:26 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/05 23:10:29 by oubelhaj         ###   ########.fr       */
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

t_hdc	*here_doc(t_list *list, t_env *env)
{
	int		i;
	int		expand;
	int		count_hdcs;
	int		count;
	int		end[2];
	t_hdc	*hdc;
	char	*hdoc_line;

	i = 0;
	expand = 1;
	count_hdcs = heredoc_count(list);
	if (!count_hdcs)
		return (0);
	hdc = init_hdc(count_hdcs);
	if (!hdc)
		return (0);
	while (list && count_hdcs > 0)
	{
		count = heredoc_count2(list);
		if (!count) // if no heredoc in current command skip to next command
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
					if (count == 1) // if is last heredoc in current command, open pipe
					{
						if (pipe(end) == -1)
							return (0);
					}
					list = list->next;
					if (is_quotes(list->token->type))
					{
						expand = 0;
						list = list->next;
					}
					hdoc_line = readline("> ");
					while (ft_strcmp(hdoc_line, list->token->value)) // while line differs from delimiter
					{
						if (count == 1) // if last heredoc in current command, write in the previously opened pipe
						{
							if (expand == 0)
								ft_putendl_fd(hdoc_line, end[1]);
							else
								heredoc_expand(hdoc_line, env, end[1]);
						}
						if (hdoc_line)
							free(hdoc_line);
						hdoc_line = readline("> ");
					}
					if (count == 1) // if is last heredoc in current command, close end[1] and save end[0] 
					{
						close(end[1]);
						hdc->fds[i] = end[0];
						i++;
					}
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
	return (hdc);
}
