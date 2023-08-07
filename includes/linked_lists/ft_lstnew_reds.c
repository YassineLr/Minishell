/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_reds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:36:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/12 00:40:12 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_reds	*ft_lstnew_reds(int fd)
{
	t_reds	*node;

	node = malloc(sizeof(t_reds));
	if (!node)
		return (0);
	node->fd = fd;
	node->next = NULL;
	return (node);
}
