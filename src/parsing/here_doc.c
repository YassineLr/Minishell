/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:49:26 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/09 03:17:43 by oubelhaj         ###   ########.fr       */
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

t_vars	*initialize_vars(t_list *list)
{
	t_vars	*vars;

	vars = init_vars();
	vars->hdc_expand = 1;
	vars->pipe_count = count_ends(list);
	vars->ends = malloc(sizeof(int *) * vars->pipe_count);
	if (!vars->ends)
		return (0);
	return (vars);
}

int	setup_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_count)
	{
		vars->ends[i] = malloc(sizeof(int) * 2);
		if (!vars->ends[i] || pipe(vars->ends[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

void    skip_to_next_cmd(t_list **list)
{
	while (*list && (*list)->token->type != PIPE)
		*list = (*list)->next;
	if (*list)
		*list = (*list)->next;
}

void	mark_hdc_quotes(t_list **list, t_vars *vars)
{
	vars->hdc_expand = 0;
	*list = (*list)->next;
}

void    open_heredoc(t_list **list, t_vars *vars, t_env *env, t_hdc *hdc)
{
	if (is_quotes((*list)->token->type))
		mark_hdc_quotes(list, vars);
	while (1)
	{
		if (!vars->count || !vars->count_hdcs)
			break ;
		vars->hdoc_line = readline("> ");
		if (!vars->hdoc_line)
			break ;
		if (ft_strcmp(vars->hdoc_line, (*list)->token->value))
		{
			if (vars->count == 1)
			{
				if (vars->hdc_expand == 0)
					ft_putendl_fd(vars->hdoc_line, vars->ends[vars->i][1]);
				else
					heredoc_expand(vars->hdoc_line, env, vars->ends[vars->i][1]);
			}
		}
		else
			break ;
		if (vars->hdoc_line)
			free(vars->hdoc_line);
	}
}
void    process_heredoc(t_list **list, t_vars *vars, t_env *env, t_hdc *hdc)
{
    while (*list && (*list)->token && (*list)->token->type != PIPE && vars->count_hdcs > 0)
	{
		if ((*list)->token->type == HEREDOC)
		{
			*list = (*list)->next;
            open_heredoc(list, vars, env, hdc);
			if (vars->count == 1)
				vars->i++;
			if (vars->hdoc_line)
				free(vars->hdoc_line);
			vars->count--;
			vars->count_hdcs--;
		}
		else
			*list = (*list)->next;
	}
}

void    close_and_exit(t_vars *vars)
{
    int i;

	i = 0;
	while (i < vars->pipe_count)
	{
		close(vars->ends[i][1]);
		i++;
	}
	exit(exitcode);
}

void	child_process(t_list *list, t_vars *vars, t_env *env, t_hdc *hdc)
{
	int	i;

	i = 0;
	signal(SIGINT, ctrl_c_hdoc);
	while (i < vars->pipe_count)
	{
		close(vars->ends[i][0]);
		i++;
	}
	while (list && vars->count_hdcs > 0)
	{
		vars->count = heredoc_count2(list);
        if (!vars->count)
            skip_to_next_cmd(&list);
        else
            process_heredoc(&list, vars, env, hdc);
	}
	close_and_exit(vars);
	exit(exitcode);
}

void	parent_process(t_vars *vars, t_hdc *hdc)
{
    int i;

	i = 0;
	while(waitpid(-1, &vars->status, 0) != -1)
		exit_status(vars->status);
	while (i < vars->pipe_count)
	{
		close(vars->ends[i][1]);
		i++;
	}
	i = 0;
	while (i < vars->pipe_count)
	{
		hdc->fds[i] = vars->ends[i][0];
		i++;
	}
}

t_hdc	*here_doc(t_list *list, t_env *env)
{
	t_hdc	*hdc;
	t_vars	*vars;

	vars = initialize_vars(list);
	if (!vars)
		return (0);
	if (!setup_pipes(vars))
		return (0);
	vars->count_hdcs = heredoc_count(list);
	if (!vars->count_hdcs)
		return (0);
	hdc = init_hdc(vars->pipe_count);
	if (!hdc)
		return (0);
	vars->pid = fork();
	if (!vars->pid)
		child_process(list, vars, env, hdc);
	else
		parent_process(vars, hdc);
	return (hdc);
}
