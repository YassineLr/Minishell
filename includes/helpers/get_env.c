/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 04:32:36 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/20 12:17:29 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*execc_get_env(char **envp)
{
	int		i;
	char	**key_val;
	t_env	*env;

	i = 0;
	env = NULL;
	key_val = malloc(sizeof(char *) * 2);
	while (envp[i])
	{
		key_val[0] = ft_strdup(ft_substr(envp[i], 0, index_at(envp[i], '=')));
		key_val[1] = ft_strdup(ft_strchr(envp[i],'=') + 1);
		ft_lstadd_back_env(&env,ft_lstnew_env(key_val));
		i++;
	}
	return (env);
}