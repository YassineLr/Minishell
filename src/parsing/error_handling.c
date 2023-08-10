/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:11:48 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/10 14:59:59 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipes(t_list *list)
{
	if (list->token->e_type == PIPE)
		return (0);
	while (list)
	{
		if (list->token->e_type == PIPE)
		{
			if (!list->next)
				return (0);
			list = list->next;
			if (list->token->e_type == WHITESPACE)
				list = list->next;
			if (list->token->e_type == PIPE)
				return (0);
		}
		list = list->next;
	}
	return (1);
}

int	redirections(t_list *list, int red_e_type)
{
	while (list)
	{
		if ((int)list->token->e_type == red_e_type)
		{
			if (!list->next)
				return (0);
			list = list->next;
			if (list)
			{
				if (list->token->e_type == WHITESPACE)
					list = list->next;
				if (list->token->e_type != WORD
					&& !is_quotes(list->token->e_type))
					return (0);
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
	if (!input || !list)
		return (2);
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
