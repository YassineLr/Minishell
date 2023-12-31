/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:11:42 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/10 02:56:58 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	delete_first_node(t_list **head, t_list **current)
{
	*head = (*current)->next;
	ft_lstdelone(*current, &free);
	*current = *head;
}

void	delete_other_nodes(t_list **current, t_list **prev)
{
	(*prev)->next = (*current)->next;
	ft_lstdelone(*current, &free);
	*current = (*prev)->next;
}

void	remove_type(t_list **head, int type)
{
	t_list	*current;
	t_list	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if ((int)current->token->e_type == type)
		{
			if (prev == NULL)
				delete_first_node(head, &current);
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

void	remove_nulls(t_list **head)
{
	t_list	*current;
	t_list	*prev;
	int		prev_type;

	prev = NULL;
	current = *head;
	prev_type = -1;
	while (current != NULL)
	{
		if (current->token->e_type == WORD && !is_quotes(prev_type)
			&& current->token->value[0] == '\0' && !is_redir(prev_type))
		{
			prev_type = current->token->e_type;
			if (prev == NULL)
				delete_first_node(head, &current);
			else
				delete_other_nodes(&current, &prev);
		}
		else
		{
			prev_type = current->token->e_type;
			prev = current;
			current = current->next;
		}
	}
}
