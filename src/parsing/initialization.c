/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:43:15 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/07 04:03:27 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_lexer(t_lexer *lexer)
{
	int	i;
	
	i = -1;
	if (!lexer)
		return;
	while (lexer->env[++i])
	{
		free(lexer->env[i]->key);
		free(lexer->env[i]->value);
		free(lexer->env[i]);
	}
	free(lexer->env);
	free(lexer);
}

void	free_list(t_list *list)
{
	if (!list)
		return;
	while (list)
	{
		if (list->token)
		{
			if (list->token->value)
				free(list->token->value);
			free(list->token);
		}
		list = list->next;
	}
	free(list);
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
	lexer->env = get_env(envp);
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
