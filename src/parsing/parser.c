/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:08:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/06 15:53:07 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_redout(t_list *list)
{
	t_reds	*r_outs;
	int		last_red;

	last_red = 1;
	r_outs = NULL;
	while (list && list->token && list->token->type != PIPE)
	{
		if (list->token->type == RED_OUT)
		{
			list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&r_outs, ft_lstnew_reds(open_redout(list), NULL));
		}
		else if (list->token->type == APPEND)
		{
			list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&r_outs, ft_lstnew_reds(open_append(list), NULL));
		}
		list = list->next;
	}
	if (r_outs)
		last_red = get_last_red_out(r_outs);
	return (last_red);
}

t_reds	*get_redin(t_list *list)
{
	t_reds	*red_ins;

	red_ins = NULL;
	while (list && list->token && list->token->type != PIPE)
	{
		if (list->token->type == RED_IN)
		{
			list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&red_ins, ft_lstnew_reds(open_redin(list), NULL));
		}
		else if (list->token->type == HEREDOC)
		{
			list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&red_ins, ft_lstnew_reds(-2, list->token->value));
		}
		list = list->next;
	}
	return (red_ins);
}

char	**get_cmds(t_list *list)
{
	int		i;
	int		count;
	char	**cmds;

	i = 0;
	count = count_parser_words(list);
	if (count == 0)
		return (NULL);
	cmds = malloc(sizeof(char *) * (count + 1));
	while (list && list->token->type != PIPE)
	{
		if (is_redir(list->token->type))
			list = list->next;
		else if (list->token->type == WORD)
			get_parser_word(list, cmds, &i);
		list = list->next;
	}
	cmds[i] = NULL;
	return (cmds);
}

t_cmd	*fill_cmd(t_list *list)
{
	t_cmd	*cmd;

	cmd = init_cmd();
	cmd->cmds = get_cmds(list);
	cmd->red_out = get_redout(list);
	cmd->red_in = get_redin(list);
	return (cmd);
}

t_parser	*ft_parser(t_list *list, t_hdc *hdc)
{
	int			i;
	t_parser	*p_list;
	t_cmd		*cmd;

	i = 0;
	p_list = NULL;
	while (list)
	{
		cmd = fill_cmd(list);
		while (list && list->token && list->token->type != PIPE)
			list = list->next;
		if (list && list->token && list->token->type == PIPE)
		{
			cmd->pipe = 1;
			list = list->next;
		}
		ft_lstadd_back_alt(&p_list, ft_lstnew_alt(cmd));
		free_cmds(cmd);
	}
	return (p_list);
}
