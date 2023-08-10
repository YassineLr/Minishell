/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:21:44 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 19:39:56 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_last_env(t_env *lst)
{
	if (!lst)
		return (0);
	if (!lst->next)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
