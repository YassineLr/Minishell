/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_reds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:36:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/06 19:19:25 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_reds	*ft_lstnew_reds(int fd, t_token *token)
{
	t_reds	*node;

	node = malloc(sizeof(t_reds));
	if (!node)
		return (0);
	node->fd = fd;
	if (token)
	{
		node->hdoc = malloc(sizeof(t_hdoc));
		node->hdoc->in = -1;
		node->hdoc->out = -1;
		node->hdoc->delim = ft_strdup(token->value);
		node->hdoc->expand = token->heredoc_expand;
	}
	else
		node->hdoc = NULL;
	node->next = NULL;
	return (node);
}
