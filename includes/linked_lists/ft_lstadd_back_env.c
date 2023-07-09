/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:26:26 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/09 22:30:27 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_lstadd_back_env(t_env **lst, t_env *new)
// {
// 	t_env	*courant;
	
// 	courant = *lst;
// 	if (*lst)
// 	{
// 		// if (!courant->next)
// 		// 	courant->next = new;
// 		// else
// 		// {
// 			while (courant)
// 			{
// 				if(courant->next == NULL)
// 				{
// 					courant->next = new;
// 					break;
// 				}
// 				courant = courant-> next;
// 			}
// 		// }
// 	}
// 	else
// 		*lst = new;
// }

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	if (*lst)
		ft_last_env(*lst)->next = new;
	else
		*lst = new;
}