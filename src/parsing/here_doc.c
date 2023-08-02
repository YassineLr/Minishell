/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:49:26 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/02 03:53:54 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			if (is_quotes((*list)->token->type))
				*list = (*list)->next;
		}
		if ((*list)->token->type != WORD)
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
		if (list->token->type == HEREDOC)
		{
			if (!handle_heredoc(&list, prev_type))
				return (count);
			else
				count++;
		}
		else
		{
			if (!hc_handle_errors(prev_type, list->token->type))
				return (count);
		}
		prev_type = list->token->type;
		list = list->next;
	}
	return (count);
}

void	expansion_v2(t_lexer *lexer, char *str, int fd, t_env *env)
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
				while (env)
				{
					if (ft_strcmp(tmp, env->key) == 0)
						break;
					env = env->next;
				}
				if (env)
					final_str = ft_strjoin(final_str, env->value);
				if (tmp)
				{
					free(tmp);
					tmp = NULL;
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
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
		}
	}
	if (final_str)
	{
		ft_putendl_fd(final_str, fd);
		free(final_str);
	}
}

int *here_doc(t_lexer *lexer, t_list *list, t_env *env)
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
			if (is_quotes(list->token->type))
			{
				expand = 0;
				list = list->next;
			}
			hdoc_line = readline("> ");
			while (ft_strcmp(hdoc_line, list->token->value))
			{
				if (i == count - 1)
				{
					if (expand == 0)
						ft_putendl_fd(hdoc_line, end[1]);
					else
						expansion_v2(lexer, hdoc_line, end[1], env);
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
