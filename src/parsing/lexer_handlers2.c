/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:17:51 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/31 12:22:26 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lexer_handle_input_redirection(t_lexer *lexer, t_list **list)
{
	if (lexer->content[lexer->i + 1] == '<')
	{
		lexer_advance(lexer);
		ft_lstadd_back(list, ft_lstnew(init_token(HEREDOC,
			ft_strdup("<<"))));
	}
	else
		ft_lstadd_back(list, ft_lstnew(init_token(RED_IN,
			lexer_char_to_string(lexer->c))));
	lexer_advance(lexer);
}

void	lexer_handle_output_redirection(t_lexer *lexer, t_list **list)
{
	if (lexer->content[lexer->i + 1] == '>')
	{
		lexer_advance(lexer);
		ft_lstadd_back(list, ft_lstnew(init_token(APPEND,
			ft_strdup(">>"))));
	}
	else
		ft_lstadd_back(list, ft_lstnew(init_token(RED_OUT,
			lexer_char_to_string(lexer->c))));
	lexer_advance(lexer);
}

void	lexer_handle_pipe(t_lexer *lexer, t_list **list)
{
	ft_lstadd_back(list, ft_lstnew(init_token(PIPE,
		lexer_char_to_string(lexer->c))));
	lexer_advance(lexer);
}

void	lexer_handle_whitespace(t_lexer *lexer, t_list **list)
{
	while (ft_is_whitespace(lexer->c))
		lexer_advance(lexer);
	ft_lstadd_back(list, ft_lstnew(init_token(WHITESPACE,
		lexer_char_to_string(' '))));
}
