/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:08:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/11 00:05:22 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_redout(t_list *list)
{
	t_reds	*r_outs;
	int		last_red;

	last_red = 1;
	r_outs = NULL;
	while (list && list->token && list->token->e_type != PIPE)
	{
		if (list->token->e_type == RED_OUT)
		{
			list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&r_outs, ft_lstnew_reds(open_redout(list)));
		}
		else if (list->token->e_type == APPEND)
		{
			list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&r_outs, ft_lstnew_reds(open_append(list)));
		}
		list = list->next;
	}
	if (r_outs)
		last_red = get_last_red_out(r_outs);
	return (last_red);
}

int	get_redin(t_list *list)
{
	t_reds	*red_ins;
	int		last_red;

	last_red = 0;
	red_ins = NULL;
	while (list && list->token && list->token->e_type != PIPE)
	{
		if (list->token->e_type == RED_IN)
		{
			list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&red_ins, ft_lstnew_reds(open_redin(list)));
		}
		else if (list->token->e_type == HEREDOC)
		{
			list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&red_ins, ft_lstnew_reds(-2));
		}
		list = list->next;
	}
	if (red_ins)
		last_red = get_last_red_in(red_ins);
	return (last_red);
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
	while (list && list->token->e_type != PIPE)
	{
		if (is_redir(list->token->e_type))
			list = list->next;
		else if (list->token->e_type == WORD)
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
	cmd->red_in = get_redin(list);
	cmd->red_out = get_redout(list);
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
		g_global.flag = 0;
		cmd = fill_cmd(list);
		if (cmd->red_in == -2)
			cmd->red_in = hdc->fds[i++];
		while (list && list->token && list->token->e_type != PIPE)
			list = list->next;
		if (list && list->token && list->token->e_type == PIPE)
		{
			cmd->pipe = 1;
			list = list->next;
		}
		ft_lstadd_back_alt(&p_list, ft_lstnew_alt(cmd));
		free_cmds(cmd);
	}
	return (p_list);
}
