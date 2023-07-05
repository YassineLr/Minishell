/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:40:21 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/05/26 18:40:21 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(char c)
{
	if (c == '\'' || c == '"' || ft_is_whitespace(c)
		|| c == '>' || c == '<' || c == '|' || c == '$')
		return (1);
	return (0);
}

char	*get_word(t_lexer *lexer)
{
	int		len;
	int		start;
	char	*word;

	len = 0;
	start = lexer->i;
	if (lexer->c == '$')
	{
		len++;
		lexer_advance(lexer);
	}
	while (lexer->c && !is_special(lexer->c))
	{
		len++;
		lexer_advance(lexer);
	}
	word = ft_substr(lexer->content, start, len);
	return (word);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c && lexer->i < ft_strlen(lexer->content))
	{
		lexer->i++;
		lexer->c = lexer->content[lexer->i];
	}
}

void	lexer_skip_whitespaces(t_lexer *lexer)
{
	while (ft_is_whitespace(lexer->c) || lexer->c == '\n')
		lexer_advance(lexer);
}

char	*get_quoted_string(t_lexer *lexer, char quotes, int hc_flag)
{
	char	*str;
	char	*tmp;
	int		expand;

	expand = 0;
	str = malloc(sizeof(char));
	if (!str)
		return (0);
	str[0] = '\0';
	if (quotes == '"' && hc_flag == 0)
		expand = 1;
	while (lexer->c && lexer->c != quotes)
	{
		if (lexer->c == '$' && !ft_is_whitespace(lexer->content[lexer->i + 1]) && expand == 1)
			str = ft_strjoin(str, expansion(lexer));
		else
		{
			tmp = lexer_char_to_string(lexer->c);
			str = ft_strjoin(str, tmp);
			free(tmp);
			lexer_advance(lexer);
		}
	}
	if (lexer->c == quotes)
		lexer_advance(lexer);
	return (str);
}

char	*lexer_char_to_string(char c)
{
	char	*str;

	str = malloc(sizeof(char) + 1);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	ft_lexer(t_lexer *lexer, t_list **list)
{
	int		len;
	int		hc_flag;

	hc_flag = 0;
	len = ft_strlen(lexer->content);
	if (ft_is_whitespace(lexer->c) || lexer->c == '\n')
		lexer_skip_whitespaces(lexer);
	while (lexer->c && lexer->i < len)
	{
		if (lexer->c == '$')
		{
			// if (lexer->content[lexer->i + 1] == '?')
			// 	exit_status();
			if (lexer->content[lexer->i + 1] == '\'' || lexer->content[lexer->i + 1] == '"')
				lexer_advance(lexer);
			else if (lexer->content[lexer->i + 1] == '$')
			{
				lexer_advance(lexer);
				lexer_advance(lexer);
				ft_lstadd_back(list, ft_lstnew(init_token(WORD, ft_strdup("$$"))));
			}
			else if (lexer->c && (ft_is_whitespace(lexer->content[lexer->i + 1]) || lexer->content[lexer->i + 1] == '\0'))
			{
				ft_lstadd_back(list, ft_lstnew(init_token(WORD, lexer_char_to_string(lexer->c))));
				lexer_advance(lexer);
			}
			else
			{
				if (hc_flag == 1)
				{
					ft_lstadd_back(list, ft_lstnew(init_token(WORD, get_word(lexer))));
					hc_flag = 0;
				}
				else
					ft_lstadd_back(list, ft_lstnew(init_token(WORD, expansion(lexer))));
			}
		}
		else if (lexer->c == '\'')
		{
			ft_lstadd_back(list, ft_lstnew(init_token(QUOTES, lexer_char_to_string(lexer->c))));
			lexer_advance(lexer);
			if (lexer->c)
				ft_lstadd_back(list, ft_lstnew(init_token(WORD, get_quoted_string(lexer, '\'', hc_flag))));
			hc_flag = 0;
		}
		else if (lexer->c == '"')
		{
			ft_lstadd_back(list, ft_lstnew(init_token(QUOTES, lexer_char_to_string(lexer->c))));
			lexer_advance(lexer);
			if (lexer->c)
				ft_lstadd_back(list, ft_lstnew(init_token(WORD, get_quoted_string(lexer, '"', hc_flag))));
			hc_flag = 0;
		}
		else if (lexer->c == '|')
		{
			ft_lstadd_back(list, ft_lstnew(init_token(PIPE, lexer_char_to_string(lexer->c))));
			lexer_advance(lexer);
		}
		else if (ft_is_whitespace(lexer->c))
		{
			if (!check_end(&lexer->content[lexer->i]))
				break;
			while (ft_is_whitespace(lexer->c))
				lexer_advance(lexer);
			ft_lstadd_back(list, ft_lstnew(init_token(WHITESPACE, lexer_char_to_string(' '))));
		}
		else if (lexer->c == '<')
		{
			if (lexer->content[lexer->i + 1] == '<')
			{
				lexer_advance(lexer);
				ft_lstadd_back(list, ft_lstnew(init_token(HEREDOC, ft_strdup("<<"))));
				hc_flag = 1;
			}
			else
				ft_lstadd_back(list, ft_lstnew(init_token(RED_IN, lexer_char_to_string(lexer->c))));
			lexer_advance(lexer);
		}
		else if (lexer->c == '>')
		{
			if (lexer->content[lexer->i + 1] == '>')
			{
				lexer_advance(lexer);
				ft_lstadd_back(list, ft_lstnew(init_token(APPEND, ft_strdup(">>"))));
			}
			else
				ft_lstadd_back(list, ft_lstnew(init_token(RED_OUT, lexer_char_to_string(lexer->c))));
			lexer_advance(lexer);
		}
		else
			ft_lstadd_back(list, ft_lstnew(init_token(WORD, get_word(lexer))));
	}
}
