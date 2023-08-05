/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:00:42 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/04 18:55:46 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_env_variable(char *str, t_env *env, int *i)
{
	char	*tmp;
	int		start;
	int		len;

	start = *i;
	len = 0;
	while (str[*i] && str[*i] != '$' && !ft_is_whitespace(str[*i]))
	{
		*i += 1;
		len++;
	}
	tmp = ft_substr(str, start, len);
	while (env)
	{
		if (ft_strcmp(tmp, env->key) == 0)
			break ;
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

char	*expand_dollar_sign(char *str, t_env *env, int *i)
{
	char	*tmp;

	*i += 1;
	tmp = NULL;
	if (str[*i] == '$')
	{
		tmp = ft_strdup("$$");
		*i += 1;
	}
	else if (str[*i] == '?')
	{
		tmp = ft_itoa(exitcode);
		*i += 1;
	}
	else
		tmp = expand_env_variable(str, env, i);
	return (tmp);
}

char	*expand_regular_text(char *str, int *i)
{
	int		start;
	int		len;

	start = *i;
	len = 0;
	while (str[*i] && str[*i] != '$')
	{
		*i += 1;
		len++;
	}
	return (ft_substr(str, start, len));
}

char	*expand_(char *str, t_env *env)
{
	int		i;
	char	*final_str;
	char	*tmp;

	i = 0;
	final_str = malloc(sizeof(char));
	if (!final_str)
		return (0);
	final_str[0] = '\0';
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = expand_dollar_sign(str, env, &i);
			final_str = ft_strjoin(final_str, tmp);
		}
		else
		{
			tmp = expand_regular_text(str, &i);
			final_str = ft_strjoin(final_str, tmp);
		}
		free(tmp);
	}
	free(str);
	return (final_str);
}
