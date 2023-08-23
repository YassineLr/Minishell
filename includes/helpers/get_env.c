/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 04:32:36 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/23 08:40:11 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*without_env(void)
{
	char	**key_val;
	t_env	*env;

	env = NULL;
	key_val = malloc(sizeof(char *) * 2);
	key_val[0] = ft_strdup("PWD");
	key_val[1] = ft_strdup("/Users/ylarhris");
	ft_lstadd_back_env(&env, ft_lstnew_env(key_val));
	free(key_val[0]);
	free(key_val[1]);
	key_val[0] = ft_strdup("SHLVL");
	key_val[1] = ft_strdup("");
	ft_lstadd_back_env(&env, ft_lstnew_env(key_val));
	free(key_val[0]);
	free(key_val[1]);
	key_val[0] = ft_strdup("_");
	key_val[1] = ft_strdup("/usr/bin/env");
	ft_lstadd_back_env(&env, ft_lstnew_env(key_val));
	free(key_val[0]);
	free(key_val[1]);
	free(key_val);
	return (env);
}

t_env	*get_env(char **envp)
{
	int		i;
	char	**key_val;
	t_env	*env;

	i = 0;
	env = NULL;
	if (!*envp)
		env = without_env();
	else
	{
		key_val = malloc(sizeof(char *) * 2);
		while (envp[i])
		{
			key_val[0] = ft_substr(envp[i], 0, index_at(envp[i], '='));
			key_val[1] = ft_strdup(ft_strchr(envp[i], '=') + 1);
			ft_lstadd_back_env(&env, ft_lstnew_env(key_val));
			free(key_val[0]);
			free(key_val[1]);
			key_val[0] = NULL;
			key_val[1] = NULL;
			i++;
		}
		free(key_val);
	}
	return (env);
}
