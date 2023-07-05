/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:11:48 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/05 15:03:13 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_end(char *input)
{
	int	i;

	i = 1;
	while (input[i] && ft_is_whitespace(input[i]))
		i++;
	if (input[i] == '\0')
		return (0);
	return (1);
}

int	check_pipes(t_list *list)
{
	if (list->token->type == PIPE)
		return (0);
	while (list)
	{
		if (list->token->type == PIPE)
		{
			if (list->next)
			{
				if (list->next->token->type == PIPE)
					return (0);
			}
			else
				return (0);
		}
		list = list->next;
	}
	return (1);
}

int	redirections(t_list *list, int red_type)
{
	while (list)
	{
		if ((int)list->token->type == red_type)
		{
			if (list->next)
			{
				list = list->next;
				if (list->token->type == WHITESPACE)
				{
					list = list->next;
					if (list->token->type != WORD && (list->token->type == QUOTES && !list->next))
						return (0);
				}
			}
			else
				return (0);
		}
		list = list->next;
	}
	return (1);
}

int	check_redirections(t_list *list)
{
	if (!redirections(list, RED_IN))
		return (0);
	if (!redirections(list, RED_OUT))
		return (0);
	if (!redirections(list, APPEND))
		return (0);
	if (!redirections(list, HEREDOC))
		return (0);
	return (1);
}

int	check_quotes(char *input)
{
	char	prev_char;
	int		in_single_quotes;
	int		in_double_quotes;

	prev_char = '\0';
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (*input)
	{
		if (*input == '\'' && prev_char != '\\' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (*input == '\"' && prev_char != '\\' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		prev_char = *input;
		input++;
	}
	return (!in_single_quotes && !in_double_quotes);
}

int	check_errors(char *input, t_list *list)
{
	int	i;

	i = 0;
	if (!input || !list)
		return (0);
	if (!check_quotes(input))
	{	
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (-1);
	}
	if (!check_pipes(list))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (0);
	}
	if (!check_redirections(list))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (0);
	}
	return (1);
}
