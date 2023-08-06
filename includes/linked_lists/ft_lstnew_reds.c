/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_reds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:36:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/06 15:48:03 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_reds	*ft_lstnew_reds(int fd, char *delim)
{
	t_reds	*node;

	node = malloc(sizeof(t_reds));
	if (!node)
		return (0);
	node->fd = fd;
	if (delim)
	{
		node->hdoc = malloc(sizeof(t_hdoc));
		node->hdoc->in = -1;
		node->hdoc->out = -1;
		node->hdoc->delim = ft_strdup(delim);
	}
	else
		node->hdoc = NULL;
	node->next = NULL;
	return (node);
}
