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

#include "../../minishell.h"

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

int	is_special(char c)
{
	if (c == '\'' || c == '"' || ft_is_whitespace(c)
		|| c == '>' || c == '<' || c == '|' || c == '$')
		return (1);
	return (0);
}

void	ft_lexer(t_lexer *lexer, t_list **list)
{
	if (ft_is_whitespace(lexer->c))
		lexer_skip_whitespaces(lexer);
	while (lexer->c)
	{
		if (lexer->c == '$')
			lexer_handle_dollar(lexer, list);
		else if (lexer->c == '\'')
			lexer_handle_single_quotes(lexer, list);
		else if (lexer->c == '"')
			lexer_handle_double_quotes(lexer, list);
		else if (lexer->c == '|')
			lexer_handle_pipe(lexer, list);
		else if (ft_is_whitespace(lexer->c))
		{
			if (!check_end(&lexer->content[lexer->i]))
				break ;
			lexer_handle_whitespace(lexer, list);
		}
		else if (lexer->c == '<')
			lexer_handle_input_redirection(lexer, list);
		else if (lexer->c == '>')
			lexer_handle_output_redirection(lexer, list);
		else
			ft_lstadd_back(list, ft_lstnew(init_token(WORD, get_word(lexer))));
	}
}
