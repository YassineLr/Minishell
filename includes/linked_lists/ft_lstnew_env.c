/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:48 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/19 14:14:11 by ylarhris         ###   ########.fr       */
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
	env->key = enviroment[0];
	if (enviroment[1])
		env->value = enviroment[1];
	else
		env->value = NULL;
	env->next = NULL;
	return (env);
}
