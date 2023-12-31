/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:49:26 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/20 00:03:37 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_heredoc(t_list **list, t_vars *vars)
{
	if (is_quotes((*list)->token->e_type))
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
			if (vars->count == 1 && is_last_redin(*list))
			{
				if (vars->hdc_expand == 0)
					ft_putendl_fd(vars->hdoc_line, vars->ends[vars->i][1]);
				else
					heredoc_expand(vars->hdoc_line, vars->ends[vars->i][1]);
			}
		}
		else
			break ;
		if (vars->hdoc_line)
			free(vars->hdoc_line);
	}
}

void	process_heredoc(t_list **list, t_vars *vars)
{
	while (*list && (*list)->token && (*list)->token->e_type != PIPE
		&& vars->count_hdcs > 0)
	{
		if ((*list)->token->e_type == HEREDOC)
		{
			*list = (*list)->next;
			open_heredoc(list, vars);
			if (vars->count == 1 && is_last_redin(*list))
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

void	child_process(t_list *list, t_vars *vars)
{
	int	i;

	i = 0;
	signal(SIGINT, ctrl_c_hdoc);
	g_global.exitcode = 0;
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
			process_heredoc(&list, vars);
	}
	close_and_exit(vars);
	exit(g_global.exitcode);
}

void	parent_process(t_vars *vars, t_hdc *hdc, int *err)
{
	int	i;

	i = -1;
	while (waitpid(-1, &vars->status, 0) != -1)
		exit_status(vars->status);
	while (++i < vars->pipe_count)
		close(vars->ends[i][1]);
	if (g_global.exitcode == 1)
	{
		i = -1;
		while (++i < vars->pipe_count)
			close(vars->ends[i][0]);
		*err = -1;
	}
	else
	{
		i = -1;
		while (++i < vars->pipe_count)
			hdc->fds[i] = vars->ends[i][0];
	}
}

t_hdc	*here_doc(t_list *list, int *err)
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
	{
		free_vars(vars);
		return (0);
	}
	hdc = init_hdc(vars);
	if (!hdc)
		return (0);
	vars->pid = fork();
	if (!vars->pid)
		child_process(list, vars);
	else
		parent_process(vars, hdc, err);
	free_vars(vars);
	return (hdc);
}
