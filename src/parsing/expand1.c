/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:03:55 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/09 01:18:23 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_expand(t_list **list, t_vars *vars, t_env *env)
{
	char	*tmp;

	if (is_before_pipe(*list))
		exitcode = 0;
	if (must_expand((*list)->token->value))
	{
		tmp = (*list)->token->value;
		(*list)->token->value = expand_((*list)->token->value, env);
		free(tmp);
		(*list)->token->expanded = 1;
		if (is_quotes(vars->prev))
			(*list)->token->in_quotes = 1;
	}
	vars->prev = (*list)->token->type;
	*list = (*list)->next;
}

void	check_flag(t_list **list, t_vars *vars, t_env *env)
{
	if (vars->flag != 1)
		handle_expand(list, vars, env);
	else
	{
		vars->flag = 0;
		*list = (*list)->next;
	}
}

void	expansion(t_list *list, t_env *env)
{
	t_vars	*vars;

	vars = init_vars();
	while (list)
	{
		if (list->token->type == HEREDOC)
			mark_hdoc(&list, vars);
		else if (list->token->type == S_QUOTES)
			mark_quotes(&list, vars);
		else if (list->token->type == WHITESPACE)
			list = list->next;
		else if (list->token->type == WORD && vars->prev == S_QUOTES
			&& vars->in_quotes)
			list_advance(&list, vars);
		else if (list->token->type == WORD && vars->prev != HEREDOC)
			check_flag(&list, vars, env);
		else
			list_advance(&list, vars);
	}
	free(vars);
}
