/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:51:20 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/31 05:52:37 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_(char *str, t_env *env)
{
	int		i;
	int		start;
	int		len;
	char	*tmp;

	len = 0;
	i = 0;
	if (str[i] == '$')
	{
		len++;
		i++;
	}
	start = i;
	while (str[i] && !is_special(str[i]))
	{
		i++;
		len++;
	}
	tmp = ft_substr(str, start, len);
	free(str);
	while (env)
	{
		if (!ft_strcmp(tmp, env->key))
			break;
		env = env->next;
	}
	if (env)
	{
		free(tmp);
		return (ft_strdup(env->value));
	}
	free(tmp);
	return (ft_strdup(""));
}

int	must_expand(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str && str[i] == '$')
		return (1);
	return (0);
}

void	expansion(t_list *list, t_env *env)
{
	char	*str;
	int		i;
	int		prev;
	int		in_quotes;

	in_quotes = 0;
	prev = -1;
	i = 0;
	while (list)
	{
		if (list->token->type == S_QUOTES)
		{
			in_quotes = !in_quotes;
			prev = list->token->type;
			list = list->next;
		}
		else if (list->token->type == WHITESPACE)
			list = list->next;
		else if (list->token->type == WORD && prev == S_QUOTES && in_quotes)
		{
			prev = list->token->type;
			list = list->next;
		}
		else if (list->token->type == WORD && prev != HEREDOC)
		{
			if (must_expand(list->token->value))
			{
				list->token->value = expand_(list->token->value, env);
				list->token->expanded = 1;
				if (prev == D_QUOTES || prev == S_QUOTES)
					list->token->in_quotes = 1;
			}
			prev = list->token->type;
			list = list->next;
		}
		else
		{
			prev = list->token->type;
			list = list->next;
		}
	}
}
