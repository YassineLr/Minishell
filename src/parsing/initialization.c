/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:43:15 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/14 08:21:20 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_lexer(t_lexer *lexer)
{
	int	i;

	i = -1;
	if (!lexer)
		return;
	ft_lstclear_env(&lexer->env, &free);
	free(lexer->content);
	free(lexer);
	lexer = NULL;
}

void	free_list(t_list **list)
{
	ft_lstclear(list, &free);
	list = NULL;
}

t_lexer	*init_lexer(char *content, char **envp)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (0);
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];
	lexer->env = execc_get_env(envp);
	return (lexer);
}

t_token *init_token(int type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->type = type;
	token->value = value;
	return (token);
}
