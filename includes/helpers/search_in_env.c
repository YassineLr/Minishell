/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 01:32:26 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/09 02:55:28 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env *search_in_env(t_env *env, char *key)
{
    t_env   *courant;

    courant = env;
    while (courant)
    {
        if(!ft_strcmp(key, courant->key))
            return (courant);
        courant = courant->next;
    }
    return(NULL);
}