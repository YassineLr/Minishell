/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 01:44:21 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/10 01:46:55 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstclear_env(t_env **lst, void (*del)(void*))
{
	t_env	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_env(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}
