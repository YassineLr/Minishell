/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:23:15 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/05 01:19:51 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_env(t_env *env)
{
    t_env *courant;

    courant = env;
    while (courant)
    {
        if(courant->key && courant->value)
            printf("%s=%s\n", courant->key, courant->value);
        courant = courant->next;
    }
}