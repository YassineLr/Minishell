/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:49:26 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/06/23 22:04:30 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_count(char *input)
{
	int		i;
	int		valid_heredoc;
	int		in_quotes;
	char	prev_char;

	i = 0;
	in_quotes = 0;
	prev_char = '\0';
	valid_heredoc = 0;
	while (input[i])
	{
		if ((input[i] == '<' && prev_char == '>') || (input[i] == '>' && prev_char == '<'))
			return (valid_heredoc);
		if (input[i] == '\"' || input[i] == '\'')
			in_quotes = !in_quotes;
		if (input[i] == '<' && input[i + 1] == '<' && prev_char != '<' && !in_quotes)
		{
			i += 2;
			if (!check_end(input + i))
				return (valid_heredoc);
			while (ft_is_whitespace(input[i]))
				i++;
			if (input[i] != '<' && input[i] != '>' && input[i] != '|')
				valid_heredoc++;
		}
		prev_char = input[i];
		i++;
	}
	return (valid_heredoc);
}

char	**get_delimiters(char *input, int count)
{
	int		i;
	int		j;
	int		len;
	int		start;
	int		in_quotes;
	char	prev_char;
	char	**delimiters;

	i = 0;
	j = 0;
	len = 0;
	start = 0;
	in_quotes = 0;
	prev_char = '\0';
	if (!count)
		return (0);
	delimiters = malloc(sizeof(char *) * (count + 1));
	if (!delimiters)
		return (0);
	while (input[i])
	{
		if ((input[i] == '<' && prev_char == '>') || (input[i] == '>' && prev_char == '<'))
		{
			delimiters[j] = NULL;
			return (delimiters);
		}
		if (input[i] == '\"' || input[i] == '\'')
			in_quotes = !in_quotes;
		if (input[i] == '<' && input[i + 1] == '<' && prev_char != '<' && !in_quotes)
		{
			i += 2;
			if (!check_end(input + i))
			{
				delimiters[j] = NULL;
				return (delimiters);
			}
			while (ft_is_whitespace(input[i]))
				i++;
			if (input[i] != '<' && input[i] != '>' && input[i] != '|')
			{
				start = i;
				len = 0;
				while (input[i] && !ft_is_whitespace(input[i]) && input[i] != '<' && input[i] != '>' && input[i] != '|')
				{
					len++;
					i++;
				}
				delimiters[j] = ft_substr(input, start, len);
				j++;
			}
		}
		prev_char = input[i];
		i++;
	}
	delimiters[j] = NULL;
	return (delimiters);
}

int	*here_doc(char *line)
{
	int		i;
	int		count;
	int		*end;
	char	*hdoc_line;
	char	**delimiters;

	i = 0;
	delimiters = NULL;
	count = heredoc_count(line);
	end = malloc(sizeof(int) * 2);
	if (!end)
		return (0);
	delimiters = get_delimiters(line, count);
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
