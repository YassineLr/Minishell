/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:11:48 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/01 09:23:10 by oubelhaj         ###   ########.fr       */
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

int	check_pipes(char *input)
{
	int	i;
	int	valid_pipes;
	int	in_quotes;
	int	prev_pipe;

	i = 0;
	valid_pipes = 1;
	in_quotes = 0;
	prev_pipe = 0;
	while (ft_is_whitespace(input[i]))
		input++;
	if (input[i] == '|')
		return (0);
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (!check_end(input + i))
				return (0);
		}
		if (input[i] == '\"' || input[i] == '\'')
			in_quotes = !in_quotes;
		else if (input[i] == '|' && !in_quotes)
		{
			if (prev_pipe)
			{
				valid_pipes = 0;
				break;
			}
			prev_pipe = 1;
		}
		else
			prev_pipe = 0;
		i++;
	}
	return (valid_pipes);
}

int	check_redirections(char *input)
{
	int		i;
	int		valid_red;
	int		in_quotes;
	int		prev_red;
	char	prev_char;

	i = 0;
	valid_red = 1;
	in_quotes = 0;
	prev_red = 0;
	prev_char = '\0';
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			if (!check_end(input + i))
				return (0);
		}	
		if (input[i] == '\"' || input[i] == '\'')
			in_quotes = !in_quotes;
		if ((input[i] == '>' || input[i] == '<') & !in_quotes)
		{
			if ((input[i] == '<' && prev_char == '>') || (input[i] == '>' && prev_char == '<'))
				return (0);
			if (prev_red > 1)
			{
				valid_red = 0;
				break;
			}
			prev_red++;
		}
		else
			prev_red = 0;
		prev_char = input[i];
		i++;
	}
	return (valid_red);
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

int	check_errors(char *input)
{
	int	i;

	i = 0;
	if (!check_quotes(input))
	{	
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (0);
	}
	if (!check_pipes(input))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (0);
	}
	if (!check_redirections(input))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (0);
	}
	return (1);
}
