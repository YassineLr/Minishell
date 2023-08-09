/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:16:49 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/09 01:18:26 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	list_advance(t_list **list, t_vars *vars)
{
	vars->prev = (*list)->token->type;
	*list = (*list)->next;
}

void	mark_hdoc(t_list **list, t_vars *vars)
{
	vars->flag = 1;
	*list = (*list)->next;
}

void	mark_quotes(t_list **list, t_vars *vars)
{
	vars->in_quotes = !vars->in_quotes;
	vars->prev = (*list)->token->type;
	*list = (*list)->next;
}

int	is_before_pipe(t_list *list)
{
	while (list)
	{
		if (list->token->type == PIPE)
			return (1);
		list = list->next;
	}
	return (0);
}

int	must_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
