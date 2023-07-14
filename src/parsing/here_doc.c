/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:49:26 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/14 09:05:55 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	expansion_v2(t_lexer *lexer, char *str, int fd)
{
	int		i;
	int		j;
	char	*tmp;
	int		start;
	int		len;
	int		s_len;
	char	*final_str;

	i = 0;
	j = 0;
	s_len = ft_strlen(str);
	final_str = malloc(sizeof(char));
	if (!final_str)
		return ;
	final_str[0] = '\0';
	while (str[i])
	{
		j = 0;
		len = 0;
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '$')
			{
				final_str = ft_strjoin(final_str, "$$");
				i++;
			}
			else
			{
				start = i;
				while (str[i] && str[i] != '$' && !ft_is_whitespace(str[i]))
				{
					i++;
					len++;
				}
				tmp = ft_substr(str, start, len);
				while (lexer->env)
				{
					if (ft_strcmp(tmp, lexer->env->key) == 0)
						break;
					lexer->env = lexer->env->next;
				}
				if (lexer->env)
				{
					final_str = ft_strjoin(final_str, lexer->env->value);
					// if (tmp)
					// 	free(tmp);
				}
			}
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
			{
				i++;
				len++;
			}
			tmp = ft_substr(str, start, len);
			final_str = ft_strjoin(final_str, tmp);
		}
		// if (tmp)
		// {
		// 	free(tmp);
		// 	tmp = NULL;
		// }
	}
	if (final_str)
		ft_putendl_fd(final_str, fd);
}

int *here_doc(t_lexer *lexer, t_list *list)
{
	int		i;
	int		expand;
	int		count;
	int		*end;
	char	*hdoc_line;

	i = 0;
	expand = 1;
	count = heredoc_count(list);
	if (!count)
		return (0);
	end = malloc(sizeof(int) * 2);
	if (!end)
		return (0);
	if (pipe(end) == -1)
		return (0);
	while (list)
	{
		if (!count)
			break;
		if (list->token->type == HEREDOC)
		{
			list = list->next;
			if (list->token->type == WHITESPACE)
				list = list->next;
			if (list->token->type == QUOTES)
			{
				expand = 0;
				list = list->next;
			}
			hdoc_line = readline("> ");
			// printf("--%s--\n", hdoc_line);
			// printf("--%s--\n", list->token->value);
			// exit(1);
			printf("%d\n", count);
			while (ft_strcmp(hdoc_line, list->token->value))
			{
				// printf("dkhl\n");
				if (i == count - 1)
				{
					if (expand == 0)
						ft_putendl_fd(hdoc_line, end[1]);
					else
						expansion_v2(lexer, hdoc_line, end[1]);
				}
				if (hdoc_line)
					free(hdoc_line);
				hdoc_line = readline("> ");
			}
			if (hdoc_line)
				free(hdoc_line);
			count--;
			if (!count)
				break;
		}
		else
			list = list->next;
	}
	close(end[1]);
	// printf("%s", get_next_line(end[0]));
	// printf("%s", get_next_line(end[0]));
	// printf("%s", get_next_line(end[0]));
	return (end);
}
