/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:12:29 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/31 12:15:33 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*lexer_char_to_string(char c)
{
	char	*str;

	str = malloc(sizeof(char) + 1);
	if (!str)
		return (0);
	str[0] = c;
	str[1] = '\0';
	return (str);
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

char	*get_quoted_string(t_lexer *lexer, char quotes)
{
	char	*str;
	char	*tmp;

	str = malloc(sizeof(char));
	if (!str)
		return (0);
	str[0] = '\0';
	while (lexer->c && lexer->c != quotes)
	{
		tmp = lexer_char_to_string(lexer->c);
		str = ft_strjoin(str, tmp);
		free(tmp);
		lexer_advance(lexer);
	}
	if (lexer->c == quotes)
		lexer_advance(lexer);
	return (str);
}
