/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:03:55 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/08 23:42:48 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	handle_expand(t_list **list, t_vars *vars, t_env *env)
{
	char	*tmp;

	if (must_expand((*list)->token->value))
	{
		if (!strcmp((*list)->token->value, "$?"))
		{
			free((*list)->token->value);
			if (is_before_pipe(*list))
				exitcode = 0;
			(*list)->token->value = ft_itoa(exitcode);
		}
		else
		{
			tmp = (*list)->token->value;
			(*list)->token->value = expand_((*list)->token->value, env);
			free(tmp);
			(*list)->token->expanded = 1;
			if (is_quotes(vars->prev))
				(*list)->token->in_quotes = 1;
		}
	}
	vars->prev = (*list)->token->type;
	*list = (*list)->next;
}

void	mark_quotes(t_list **list, t_vars *vars)
{
	vars->in_quotes = !vars->in_quotes;
	vars->prev = (*list)->token->type;
	*list = (*list)->next;
}

void	expansion(t_list *list, t_env *env)
{
	t_vars	*vars;

	vars = init_vars();
	while (list)
	{
		if (list->token->type == HEREDOC)
		{
			vars->flag = 1;
			list = list->next;
		}
		else if (list->token->type == S_QUOTES)
			mark_quotes(&list, vars);
		else if (list->token->type == WHITESPACE)
			list = list->next;
		else if (list->token->type == WORD && vars->prev == S_QUOTES
			&& vars->in_quotes)
		{
			vars->prev = list->token->type;
			list = list->next;
		}
		else if (list->token->type == WORD && vars->prev != HEREDOC)
		{
			if (vars->flag != 1)
				handle_expand(&list, vars, env);
			else
			{
				vars->flag = 0;
				list = list->next;
			}
		}
		else
		{
			vars->prev = list->token->type;
			list = list->next;
		}
	}
	free(vars);
}
