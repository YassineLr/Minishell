/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:03:55 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/10 02:01:30 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_expand(t_list **list, t_vars *vars)
{
	char	*tmp;

	if (is_before_pipe(*list))
		g_global.exitcode = 0;
	if (must_expand((*list)->token->value))
	{
		tmp = (*list)->token->value;
		(*list)->token->value = expand_((*list)->token->value);
		free(tmp);
		(*list)->token->expanded = 1;
		if (is_quotes(vars->prev))
			(*list)->token->in_quotes = 1;
	}
	vars->prev = (*list)->token->e_type;
	*list = (*list)->next;
}

void	check_flag(t_list **list, t_vars *vars)
{
	if (vars->flag != 1)
		handle_expand(list, vars);
	else
	{
		vars->flag = 0;
		*list = (*list)->next;
	}
}

void	expansion(t_list *list)
{
	t_vars	*vars;

	vars = init_vars();
	while (list)
	{
		if (list->token->e_type == HEREDOC)
			mark_hdoc(&list, vars);
		else if (list->token->e_type == S_QUOTES)
			mark_quotes(&list, vars);
		else if (list->token->e_type == WHITESPACE)
			list = list->next;
		else if (list->token->e_type == WORD && vars->prev == S_QUOTES
			&& vars->in_quotes)
			list_advance(&list, vars);
		else if (list->token->e_type == WORD && vars->prev != HEREDOC)
			check_flag(&list, vars);
		else
			list_advance(&list, vars);
	}
	free(vars);
}

void	search_env(t_env **env, char *tmp)
{
	while (*env)
	{
		if (ft_strcmp(tmp, (*env)->key) == 0)
			break ;
		*env = (*env)->next;
	}
}
