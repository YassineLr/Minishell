/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:21:44 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/09 22:32:48 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env   *ft_last_env(t_env *lst)
{
    if (!lst)
		return (0);
    if(!lst->next)
        return(lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}