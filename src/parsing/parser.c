/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:08:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/13 00:42:37 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_words(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->token->type != WORD && list->token->type != WHITESPACE)
			break;
		list = list->next;
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
	cmd->cmds = 0;
	cmd->pipe = 0;
	return (cmd);
}

t_parser	*ft_parser(t_list *list, int *hdc_pipe)
{
	t_list		*node;
	t_parser	*p_list;
	t_reds		*red_in = NULL;
	t_reds		*red_out = NULL;
	/*  while redirection is found open the file and save fds to close later,
		except for the last redirection. then save only the last fd of red_in
		and last of red_out in the parser list, along with the command */

	node = list;
	while (node && node->token->type != PIPE)
	{
		if (node->token->type == RED_IN)
		{
			node = node->next;
			if (node->token->type == WHITESPACE)
				node = node->next;
			ft_lstadd_back_reds(&red_in, ft_lstnew_reds(open_redin(node->token->value)));
		}
		else if (node->token->type == RED_OUT || node->token->type == APPEND)
		{
			node = node->next;
			if (node->token->type == WHITESPACE)
				node = node->next;
			if (node->token->type == RED_OUT)
				ft_lstadd_back_reds(&red_out, ft_lstnew_reds(open_redout(node->token->value)));
			else
				ft_lstadd_back_reds(&red_out, ft_lstnew_reds(open_append(node->token->value)));
		}
		node = node->next;
	}
	// when pipe is found finish the t_parser node and proceed to the next one, inside a big loop.
	while (red_in)
	{
		printf("%d\n", red_in->fd);
		red_in = red_in->next;
	}
	exit(1);
	p_list = NULL;
	(void)hdc_pipe;
	return (p_list);
}
