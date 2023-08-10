/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 01:32:26 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 19:38:56 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*search_in_env(char *key)
{
	t_env	*courant;

	if (!g_global.env)
		return (NULL);
	courant = g_global.env;
	while (courant)
	{
		if (!ft_strcmp(key, courant->key))
			return (courant);
		courant = courant->next;
	}
	return (NULL);
}
