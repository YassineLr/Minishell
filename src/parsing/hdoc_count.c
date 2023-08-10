/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 04:32:27 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/10 15:08:36 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	heredoc_count3(t_list **list)
{
	int	count;
	int	prev_type;

	count = 0;
	prev_type = -1;
	while (*list && (*list)->token->e_type != PIPE)
	{
		if ((*list)->token->e_type == HEREDOC)
		{
			count = 1;
			if (!handle_heredoc(list, prev_type))
				return (count);
			else
				count = 1;
		}
		else if ((*list)->token->e_type == RED_IN)
			count = 0;
		else
		{
			if (!hc_handle_errors(prev_type, (*list)->token->e_type))
				return (count);
		}
		advance_in_list(list, &prev_type);
	}
	return (count);
}

int	heredoc_count2(t_list *list)
{
	int	count;
	int	prev_type;

	count = 0;
	prev_type = -1;
	while (list && list->token->e_type != PIPE)
	{
		if (list->token->e_type == HEREDOC)
		{
			if (!handle_heredoc(&list, prev_type))
				return (count);
			else
				count++;
		}
		else
		{
			if (!hc_handle_errors(prev_type, list->token->e_type))
				return (count);
		}
		prev_type = list->token->e_type;
		list = list->next;
	}
	return (count);
}

int	hc_handle_errors(int prev_type, int curr_type)
{
	if (curr_type == PIPE && (is_redir(prev_type) || prev_type == PIPE))
		return (0);
	else if (curr_type == RED_IN && is_redir_2(prev_type))
		return (0);
	else if (curr_type == RED_OUT && is_redir_2(prev_type))
		return (0);
	else if (curr_type == APPEND && is_redir_2(prev_type))
		return (0);
	return (1);
}

int	handle_heredoc(t_list **list, int prev_type)
{
	if (is_redir_2(prev_type) || is_quotes(prev_type))
		return (0);
	if ((*list)->next)
	{
		*list = (*list)->next;
		if ((*list)->next)
		{
			if (is_quotes((*list)->token->e_type))
				*list = (*list)->next;
		}
		if ((*list)->token->e_type != WORD)
			return (0);
	}
	else
		return (0);
	return (1);
}

int	heredoc_count(t_list *list)
{
	int	count;
	int	prev_type;

	count = 0;
	prev_type = -1;
	while (list)
	{
		if (list->token->e_type == HEREDOC)
		{
			if (!handle_heredoc(&list, prev_type))
				return (count);
			else
				count++;
		}
		else
		{
			if (!hc_handle_errors(prev_type, list->token->e_type))
				return (count);
		}
		prev_type = list->token->e_type;
		list = list->next;
	}
	return (count);
}
