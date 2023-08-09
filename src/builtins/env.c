/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:23:15 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/09 21:06:07 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_env(void)
{
    t_env *courant;

    if(global.env)
    {
        courant = global.env;
        while (courant)
        {
            if(courant->key && courant->value)
            {
                if(!courant->value)
                    printf("%s=\n", courant->key);
                else
                    printf("%s=%s\n", courant->key, courant->value);
            }
            courant = courant->next;
        }
    }
    global.exitcode = 0;
}