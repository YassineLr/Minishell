/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 00:48:41 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/10 01:47:01 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstdelone_env(t_env *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->key);
	del(lst->value);
	del(lst);
}
