/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:08:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/15 03:06:20 by oubelhaj         ###   ########.fr       */
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
	cmd->pipe_fd = 0;
	cmd->red_in = 0;
	cmd->red_out = 0;
	cmd->heredoc = 0;
	return (cmd);
}

int	get_redout(t_list *list)
{
	t_reds	*red_outs;
	int		last_red;

	last_red = -1;
	red_outs = NULL;
	while (list)
	{
		if (!list->token)
			break;
		if (list->token->type == PIPE)
			break;
		if (list->token->type == RED_OUT)
		{
			list = list->next;
			if (list && list->token && list->token->type == WHITESPACE)
				list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&red_outs, ft_lstnew_reds(open_redout(list->token->value)));
		}
		else if (list->token->type == APPEND)
		{
			list = list->next;
			if (list && list->token && list->token->type == WHITESPACE)
				list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&red_outs, ft_lstnew_reds(open_append(list->token->value)));
		}
		list = list->next;
	}
	if (red_outs)
	{
		while (red_outs->next)
			red_outs = red_outs->next;
		last_red = red_outs->fd;
	}
	ft_lstclear_reds(&red_outs);
	return (last_red);
}

int	get_redin(t_list *list)
{
	t_reds	*red_ins;
	int		last_red;

	last_red = -1;
	red_ins = NULL;
	while (list)
	{
		if (!list->token)
			break;
		if (list->token->type == PIPE)
			break;
		if (list->token->type == RED_IN)
		{
			list = list->next;
			if (list && list->token && list->token->type == WHITESPACE)
				list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&red_ins, ft_lstnew_reds(open_redin(list->token->value)));
		}
		list = list->next;
	}
	if (red_ins)
		last_red = red_ins->fd;
	ft_lstclear_reds(&red_ins);
	return (last_red);
}

// char	**get_cmds(t_list *list)
// {
// 	char	**cmds;

	
// 	return (cmds);
// }

// t_parser	*ft_parser(t_list *list, int *hdc_pipe)
// {
// 	t_parser	*p_list;
// 	t_cmd		*cmd;
// 	/*  while redirection is found open the file and save fds to close later,
// 		except for the last redirection. then save only the last fd of red_in
// 		and last of red_out in the parser list, along with the command */

// 	while (1)
// 	{
// 		if (!list)
// 			break;
// 		cmd = init_cmd();
// 		while (list && list->token->type != PIPE)
// 		{
// 			cmd->cmds = get_cmds(list);
// 			cmd->red_in = get_redin(list);
// 			cmd->red_out = get_redout(list);
// 			printf("%d\n", cmd->red_out);
// 			exit(1);
// 			list = list->next;
// 		}
// 		// else
// 			// set pipe to 1 and advance in list
// 		// init a t_parser node here and initialize it with its values;
// 	}
// 	p_list = NULL;
// 	(void)hdc_pipe;
// 	return (p_list);
// }
