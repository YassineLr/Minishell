/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:48 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/24 01:29:13 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_lstnew_env(char **enviroment)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	if (!enviroment[0])
		return (NULL);
	env->key = ft_strdup(enviroment[0]);
	if (enviroment[1])
		env->value = ft_strdup(enviroment[1]);
	else
		env->value = NULL;
	env->next = NULL;
	return (env);
}
