/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_alt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 05:34:59 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/07 04:01:54 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_parser	*ft_lstnew_alt(t_cmd *cmd)
{
	t_parser	*node;

	node = malloc(sizeof(t_parser));
	if (!node)
		return (0);
	node->command = cmd;
	node->next = NULL;
	return (node);
}
