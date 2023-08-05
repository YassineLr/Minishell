/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:20:40 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/04 15:50:06 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_word(t_list **tmp_list, t_vars *vars)
{
	vars->tmp = malloc(sizeof(char));
	if (!vars->tmp)
		return ;
	vars->tmp[0] = '\0';
	while (*tmp_list && (*tmp_list)->token)
	{
		if ((*tmp_list)->token->type == WORD)
		{
			vars->tmp = ft_strjoin(vars->tmp, (*tmp_list)->token->value);
			if ((*tmp_list)->token->expanded)
				vars->expand = 1;
			if ((*tmp_list)->token->in_quotes)
				vars->in_quotes = 1;
			*tmp_list = (*tmp_list)->next;
		}
		else if (is_quotes((*tmp_list)->token->type))
		{
			vars->flag = 1;
			*tmp_list = (*tmp_list)->next;
		}
		else
			break ;
	}
}

void	add_joined_words(t_list **list, t_vars *vars)
{
	t_token	*token;

	token = NULL;
	if (vars->flag == 1)
	{
		ft_lstadd_back(list, ft_lstnew(init_token(S_QUOTES,
					lexer_char_to_string('\''))));
	}
	token = init_token(WORD, ft_strdup(vars->tmp));
	if (vars->expand == 1)
		token->expanded = 1;
	if (vars->in_quotes == 1)
		token->in_quotes = 1;
	ft_lstadd_back(list, ft_lstnew(token));
	free(vars->tmp);
}

t_list	**join_words(t_list **list, t_list *tmp_list)
{
	t_vars	*vars;

	vars = init_vars();
	if (!vars)
		return (0);
	while (tmp_list)
	{
		if (tmp_list->token->type != WORD && !is_quotes(tmp_list->token->type))
		{
			ft_lstadd_back(list, ft_lstnew(init_token(tmp_list->token->type,
						ft_strdup(tmp_list->token->value))));
			tmp_list = tmp_list->next;
		}
		else
		{
			process_word(&tmp_list, vars);
			add_joined_words(list, vars);
		}
		if (!tmp_list)
			break ;
	}
	free(vars);
	return (list);
}
