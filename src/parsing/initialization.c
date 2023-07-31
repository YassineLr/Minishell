/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:43:15 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/30 04:35:56 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_lexer(t_lexer *lexer)
{
	int	i;

	i = -1;
	if (!lexer)
		return;
	free(lexer->content);
	free(lexer);
	lexer = NULL;
}

void	free_plist(t_parser **list)
{
	int			i = 0;
	t_parser	*tmp;

	tmp = NULL;
	if (!list)
		return ;
	while (*list)
	{
		i = -1;
		while ((*list)->command->cmds[++i])
			free((*list)->command->cmds[i]);
		free((*list)->command->cmds[i]);
		free((*list)->command->cmds);
		free((*list)->command);
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	free_list(t_list **list)
{
	ft_lstclear(list, &free);
	list = NULL;
}

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (0);
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];
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
	token->expanded = 0;
	token->in_quotes = 0;
	return (token);
}
