/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:03:48 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/09 23:50:43 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	search_env(t_env **env, char *tmp)
{
	while (*env)
	{
		if (ft_strcmp(tmp, (*env)->key) == 0)
			break ;
		*env = (*env)->next;
	}
}
char	*expand_env_variable(char *str, int *i)
{
	char	*tmp;
	int		start;
	int		len;
	t_env	*env;

	env = global.env;
	start = *i;
	len = 0;
	while (str[*i] && ft_isalnum(str[*i]))
	{
		*i += 1;
		len++;
	}
	tmp = ft_substr(str, start, len);
	search_env(&env, tmp);
	if (env)
	{
		free(tmp);
		return (ft_strdup(env->value));
	}
	free(tmp);
	return (ft_strdup(""));
}

char	*expand_dollar_sign(char *str, int *i)
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
		tmp = ft_itoa(global.exitcode);
		*i += 1;
	}
	else if (!ft_isalnum(str[*i]) || str[*i] == '\0')
		return (ft_strdup("$"));
	else
		tmp = expand_env_variable(str, i);
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

char	*expand_(char *str)
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
			tmp = expand_dollar_sign(str, &i);
			final_str = ft_strjoin(final_str, tmp);
		}
		else
		{
			tmp = expand_regular_text(str, &i);
			final_str = ft_strjoin(final_str, tmp);
		}
		free(tmp);
	}
	return (final_str);
}

void	heredoc_expand(char *str, int fd)
{
	char	*final_str;

	final_str = expand_(str);
	if (final_str)
	{
		ft_putendl_fd(final_str, fd);
		free(final_str);
	}
}
