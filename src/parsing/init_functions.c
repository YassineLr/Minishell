/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:06:23 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/09 03:05:07 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

t_token	*init_token(int type, char *value)
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

t_vars	*init_vars(void)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (0);
	vars->expand = 0;
	vars->in_quotes = 0;
	vars->flag = 0;
	vars->tmp = 0;
	vars->prev = -1;
	vars->pid = 0;
	vars->hdc_expand = 1;
	vars->count_hdcs = 0;
	vars->count = 0;
	vars->ends = 0;
	vars->pipe_count = 0;
	vars->status = 0;
	vars->i = 0;
	vars->hdoc_line = 0;
	return (vars);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->cmds = 0;
	cmd->pipe = 0;
	cmd->red_in = 0;
	cmd->red_out = 0;
	return (cmd);
}
