/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:51:20 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/03 17:34:44 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_(char *str, t_env *env)
{
	int		i;
	char	*tmp;
	int		start;
	int		len;
	char	*final_str;

	i = 0;
	final_str = malloc(sizeof(char));
	if (!final_str)
		return (NULL);
	final_str[0] = '\0';
	while (str[i])
	{
		len = 0;
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '$')
			{
				final_str = ft_strjoin(final_str, "$$");
				i++;
			}
			else if (str[i] == '?')
			{
				final_str = ft_strjoin(final_str, ft_itoa(exitcode));
				i++;
			}
			else
			{
				start = i;
				while (str[i] && str[i] != '$' && !ft_is_whitespace(str[i]))
				{
					i++;
					len++;
				}
				tmp = ft_substr(str, start, len);
				while (env)
				{
					if (ft_strcmp(tmp, env->key) == 0)
						break;
					env = env->next;
				}
				if (env)
					final_str = ft_strjoin(final_str, env->value);
				if (tmp)
				{
					free(tmp);
					tmp = NULL;
				}
			}
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
			{
				i++;
				len++;
			}
			tmp = ft_substr(str, start, len);
			final_str = ft_strjoin(final_str, tmp);
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
		}
	}
	return (final_str);
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
				if (is_quotes(prev))
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
