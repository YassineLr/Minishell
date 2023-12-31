/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:03:33 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/05 23:03:35 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lexer_handle_dollar(t_lexer *lexer, t_list **list)
{
	if (lexer->content[lexer->i + 1] == '\''
		|| lexer->content[lexer->i + 1] == '"')
		lexer_advance(lexer);
	else if (lexer->content[lexer->i + 1] == '?')
	{
		ft_lstadd_back(list, ft_lstnew(init_token(WORD, ft_strdup("$?"))));
		lexer_advance(lexer);
		lexer_advance(lexer);
	}
	else if (lexer->content[lexer->i + 1] == '$')
	{
		lexer_advance(lexer);
		lexer_advance(lexer);
		ft_lstadd_back(list, ft_lstnew(init_token(WORD, ft_strdup("$$"))));
	}
	else if (!ft_isalnum(lexer->content[lexer->i + 1]))
	{
		ft_lstadd_back(list, ft_lstnew(init_token(WORD, ft_strdup("$"))));
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
