/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_alt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 05:35:29 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/01 08:17:39 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_alt(t_parser **lst, t_parser *new)
{
	if (*lst)
		ft_lstlast_alt(*lst)->next = new;
	else
		*lst = new;
}
