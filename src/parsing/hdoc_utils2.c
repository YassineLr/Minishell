/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 04:37:18 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/09 05:44:03 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	skip_to_next_cmd(t_list **list)
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

void	close_and_exit(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_count)
	{
		close(vars->ends[i][1]);
		i++;
	}
	exit(exitcode);
}