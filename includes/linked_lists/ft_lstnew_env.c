/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:48 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/10 19:29:59 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_lstnew_env(char **enviroment)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	if (!enviroment[0] || !enviroment[1])
		return (NULL);
	env->key = enviroment[0];
	env->value = enviroment[1];
	env->next = NULL;
	return (env);
}
