/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:11:42 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/04 17:33:17 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_type(t_list **head, int type)
{
	t_list *current;
	t_list *prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if ((int)current->token->type == type)
		{
			if (prev == NULL)
			{
				*head = current->next;
				ft_lstdelone(current, &free);
				current = *head;
			}
			else
			{
				prev->next = current->next;
				ft_lstdelone(current, &free);
				current = prev->next;
			}
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
