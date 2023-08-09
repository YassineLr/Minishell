/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 01:32:26 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/09 18:45:27 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env *search_in_env(char *key)
{
    t_env   *courant;

    if(!global.env)
        return NULL;
    courant = global.env;
    while (courant)
    {
        if(!ft_strcmp(key, courant->key))
            return (courant);
        courant = courant->next;
    }
    return(NULL);
}