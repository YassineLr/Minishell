/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:49:26 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/03 13:34:03 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_count(t_list *list)
{
	int	count;
	int	prev_type;

	count = 0;
	prev_type = -1;
	while (list)
	{
		if (list->token->type == WHITESPACE)
			list = list->next;
		if (list->token->type == HEREDOC)
		{
			if (prev_type == RED_IN || prev_type == RED_OUT
				|| prev_type == APPEND || prev_type == QUOTES)
				return (count);
			if (list->next)
			{
				list = list->next;
				if (list->token->type == WHITESPACE)
					list = list->next;
				if (list->next)
				{
					if (list->token->type == QUOTES)
						list = list->next;
				}
				if (list->token->type != WORD)
					return (count);
			}
			else
				return (count);
			count++;
		}
		else
		{
			if (list->token->type == PIPE && (prev_type == RED_IN
				|| prev_type == RED_OUT || prev_type == PIPE || prev_type == APPEND))
				return (count);
			else if (list->token->type == RED_IN
				&& (prev_type == RED_IN || prev_type == RED_OUT || prev_type == APPEND))
				return (count);
			else if (list->token->type == RED_OUT
				&& (prev_type == RED_OUT || prev_type == RED_IN || prev_type == APPEND))
				return (count);
			else if (list->token->type == APPEND && (prev_type == RED_IN
				|| prev_type == RED_OUT || prev_type == APPEND))
				return (0);
		}
		prev_type = list->token->type;
		list = list->next;
	}
	return (count);
}

char	**get_delimiters(t_list *list, int count)
{
	int		i;
	char	**delimiters;

	i = 0;
	delimiters = malloc(sizeof(char *) * (count + 1));
	if (!delimiters)
		return (0);
	while (list)
	{
		if (list->token->type == HEREDOC && count > 0)
		{
			list = list->next;
			if (list->next)
			{
				if (list->token->type == WHITESPACE)
					list = list->next;
			}
			if (list->token->type == WORD)
			{
				delimiters[i] = ft_strdup(list->token->value);
				i++;
			}
			else
				return (0);
			count--;
		}
		list = list->next;
	}
	delimiters[i] = NULL;
	// i = -1;
	// while (delimiters[++i])
	// 	printf("%s\n", delimiters[i]);
	// exit(1);
	return (delimiters);
}

int	*here_doc(t_list *list)
{
	int		i;
	int		count;
	int		*end;
	char	*hdoc_line;
	char	**delimiters;

	i = 0;
	count = heredoc_count(list);
	printf("%d\n", count);
	exit(1);
	if (!count)
		return (NULL);
	end = malloc(sizeof(int) * 2);
	if (!end)
		return (0);
	delimiters = get_delimiters(list, count);
	if (pipe(end) == -1)
		return (0);
	while (i < count)
	{
		hdoc_line = readline("> ");
		while (ft_strcmp(hdoc_line, delimiters[i]))
		{
			if (i == count - 1)
				ft_putendl_fd(hdoc_line, end[1]);
			if (hdoc_line)
				free(hdoc_line);
			hdoc_line = readline("> ");
		}
		if (hdoc_line)
			free(hdoc_line);
		i++;
	}
	close(end[1]);
	// printf("%s", get_next_line(end[0]));
	// printf("%s", get_next_line(end[0]));
	// printf("%s", get_next_line(end[0]));
	if (delimiters)
		ft_free_strs(delimiters);
	return (end);
}
