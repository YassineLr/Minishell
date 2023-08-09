/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 04:35:42 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/09 04:37:36 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
