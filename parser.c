/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:08:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/06/28 05:52:07 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(t_list *list)
{
	int	type;
	int	count;

	count = 0;
	type = list->token->type;
	while (list)
	{
		if (list->token->type != WORD)
			break;
		count++;
	}
	return (count);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->pipe = 0;
	cmd->red_in = 0;
	cmd->red_out = 0;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->cmds = 0;
	return (cmd);
}

t_parser	*parser(t_list *list, int *hdc_pipe)
{
	int			i;
	int			hdc;
	int			count;
	t_cmd		*cmd;
	t_parser	*p_list;

	i = 0;
	while (list)
	{
		cmd = init_cmd();
		if (!cmd)
			return (0);
		count = count_words(list);
		cmd->cmds = malloc(sizeof(char *) * (count + 1));
		while (list && list->token->type == WORD)
		{
			cmd->cmds[i] = ft_strdup(list->token->value);
			list = list->next;
			i++;
		}
		cmd->cmds[i] = NULL;
		if (list)
		{
			if (list->token->type == PIPE)
				cmd->pipe = 1;
			else if (list->token->type = RED_IN)
			{
				list = list->next;
				cmd->red_in = open_redin();
			}
			else if (list->token->type == RED_OUT)
			{
				list = list->next;
				cmd->red_out = open_redout();
			}
			else if (list->token->type == APPEND)
			{
				list = list->next;
				cmd->red_in = open_append();
			}
		}
		ft_lstadd_back_alt(&p_list, ft_lstnew_alt(cmd));
		if (cmd->cmds)
			ft_free_strs(cmd->cmds);
		if (cmd)
			free(cmd);
	}
	return (p_list);
}
