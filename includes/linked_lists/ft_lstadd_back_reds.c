/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_reds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:32:40 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/12 00:33:33 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstadd_back_reds(t_reds **lst, t_reds *new)
{
	if (*lst)
		ft_lstlast_reds(*lst)->next = new;
	else
		*lst = new;
}
