/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 04:35:42 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/10 15:09:38 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_hdc	*init_hdc(t_vars *vars)
{
	t_hdc	*hdc;

	hdc = malloc(sizeof(t_hdc));
	if (!hdc)
	{
		free_vars(vars);
		return (0);
	}
	hdc->count = vars->pipe_count;
	hdc->fds = malloc(sizeof(int) * vars->pipe_count);
	if (!hdc->fds)
	{
		free_vars(vars);
		return (0);
	}
	return (hdc);
}

int	count_ends(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		count += heredoc_count3(&list);
		if (list && list->token->e_type == PIPE)
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
	if (!vars)
		return (0);
	vars->hdc_expand = 1;
	vars->pipe_count = count_ends(list);
	vars->ends = malloc(sizeof(int *) * vars->pipe_count);
	if (!vars->ends)
	{
		free(vars);
		return (0);
	}
	return (vars);
}

void	advance_in_list(t_list **list, int *prev_type)
{
	*prev_type = (*list)->token->e_type;
	*list = (*list)->next;
}
