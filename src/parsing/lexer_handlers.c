/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:16:11 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/03 17:27:53 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lexer_handle_dollar(t_lexer *lexer, t_list **list)
{
	if (lexer->content[lexer->i + 1] == '?')
	{
		ft_lstadd_back(list, ft_lstnew(init_token(WORD, ft_strdup("$?"))));
		lexer_advance(lexer);
		lexer_advance(lexer);
	}
	else if (lexer->content[lexer->i + 1] == '\''
		|| lexer->content[lexer->i + 1] == '"')
		lexer_advance(lexer);
	else if (lexer->content[lexer->i + 1] == '$')
	{
		lexer_advance(lexer);
		lexer_advance(lexer);
		ft_lstadd_back(list, ft_lstnew(init_token(WORD, ft_strdup("$$"))));
	}
	else if (lexer->c && (ft_is_whitespace(lexer->content[lexer->i + 1])
		|| lexer->content[lexer->i + 1] == '\0'))
	{
		ft_lstadd_back(list, ft_lstnew(init_token(WORD,
			lexer_char_to_string(lexer->c))));
		lexer_advance(lexer);
	}
	else
		ft_lstadd_back(list, ft_lstnew(init_token(WORD, get_word(lexer))));
}

void	lexer_handle_single_quotes(t_lexer *lexer, t_list **list)
{
	ft_lstadd_back(list, ft_lstnew(init_token(S_QUOTES,
		lexer_char_to_string(lexer->c))));
	lexer_advance(lexer);
	if (lexer->c)
	{
		ft_lstadd_back(list, ft_lstnew(init_token(WORD,
			get_quoted_string(lexer, '\''))));
		ft_lstadd_back(list, ft_lstnew(init_token(S_QUOTES,
			lexer_char_to_string('\''))));
	}
}

void	lexer_handle_double_quotes(t_lexer *lexer, t_list **list)
{
	ft_lstadd_back(list, ft_lstnew(init_token(D_QUOTES,
		lexer_char_to_string(lexer->c))));
	lexer_advance(lexer);
	if (lexer->c)
	{
		ft_lstadd_back(list, ft_lstnew(init_token(WORD,
			get_quoted_string(lexer, '"'))));
		ft_lstadd_back(list, ft_lstnew(init_token(D_QUOTES,
			lexer_char_to_string('"'))));
	}
}
