/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:08:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/11 02:59:03 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_reds(t_list *list, t_redir *reds)
{
	t_reds	*r_outs;
	t_reds	*r_ins;

	r_outs = NULL;
	r_ins = NULL;
	while (list && list->token && list->token->e_type != PIPE)
	{
		if (list->token->e_type == RED_OUT || list->token->e_type == APPEND)
		{
			if (!red_out(&list, &r_outs, list->token->e_type))
				break ;
		}
		else if (list->token->e_type == RED_IN
			|| list->token->e_type == HEREDOC)
		{
			if (!red_in(&list, &r_ins, list->token->e_type))
				break ;
		}
		list = list->next;
	}
	get_last_reds(r_outs, r_ins, reds);
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
	t_redir	reds;

	cmd = init_cmd();
	cmd->cmds = get_cmds(list);
	get_reds(list, &reds);
	cmd->red_out = reds.red_out;
	cmd->red_in = reds.red_in;
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
