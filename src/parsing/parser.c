/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:08:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/24 01:46:07 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_cmds(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->token && list->token->type == PIPE)
			count++;
		list = list->next;
	}
	return (count + 1);
}

int	count_words(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->token->type == RED_IN || list->token->type == RED_OUT || list->token->type == APPEND
			|| list->token->type == HEREDOC)
			list = list->next;
		else if (list->token->type == PIPE)
			break;
		else
			count++;
		list = list->next;
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
	cmd->red_in = 0;
	cmd->red_out = 0;
	return (cmd);
}

int	get_redout(t_list *list)
{
	t_reds	*red_outs;
	int		last_red;

	last_red = 1;
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
			if (list && list->token)
				ft_lstadd_back_reds(&red_outs, ft_lstnew_reds(open_redout(list->token->value)));
		}
		else if (list->token->type == APPEND)
		{
			list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&red_outs, ft_lstnew_reds(open_append(list->token->value)));
		}
		list = list->next;
	}
	if (red_outs)
	{
		while (red_outs->next)
		{
			close(red_outs->fd);
			red_outs = red_outs->next;
		}
		last_red = red_outs->fd;
	}
	ft_lstclear_reds(&red_outs);
	return (last_red);
}

int	is_last_hc(t_list *list)
{
	while (list && list->token)
	{
		if (list->token->type == HEREDOC)
			return (0);
		list = list->next;
	}
	return (1);
}

int	get_redin(t_list *list)
{
	t_reds	*red_ins;
	int		last_red;

	last_red = 0;
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
			if (list && list->token)
				ft_lstadd_back_reds(&red_ins, ft_lstnew_reds(open_redin(list->token->value)));
		}
		else if (list->token->type == HEREDOC)
		{
			list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&red_ins, ft_lstnew_reds(-2));
		}
		list = list->next;
	}
	if (red_ins)
	{
		while (red_ins->next)
		{
			close(red_ins->fd);
			red_ins = red_ins->next;
		}
		if (red_ins->fd == -2)
		{
			if (is_last_hc(list))
			{
				ft_lstclear_reds(&red_ins);
				last_red = -2;
			}
			else
				last_red = -1;
		}
		else
			last_red = red_ins->fd;
	}
	return (last_red);
}

char	**get_cmds(t_list *list)
{
	int		i;
	char	**cmds;

	i = 0;
	cmds = malloc(sizeof(char *) * (count_words(list) + 1));
	while (list)
	{
		if (list->token->type == RED_IN || list->token->type == RED_OUT || list->token->type == APPEND
			|| list->token->type == HEREDOC)
			list = list->next;
		else if (list->token->type == PIPE)
			break;
		else if (list->token->type == WORD)
		{
			cmds[i] = ft_strdup(list->token->value);
			i++;
		}
		list = list->next;
	}
	cmds[i] = NULL;
	return (cmds);
}

t_parser	*ft_parser(t_list *list, int *hdc_pipe)
{
	t_parser	*p_list;
	t_cmd		**cmd;
	int			i;

	(void)hdc_pipe;
	i = 0;
	p_list = NULL;
	cmd = malloc(sizeof(char *) * (count_cmds(list) + 1));
	while (1)
	{
		if (!list)
			break;
		cmd[i] = init_cmd();
		cmd[i]->cmds = get_cmds(list);
		cmd[i]->red_out = get_redout(list);
		cmd[i]->red_in = get_redin(list);
		if (cmd[i]->red_in == -2)
			cmd[i]->red_in = hdc_pipe[0];
		while (list && list->token && list->token->type != PIPE)
			list = list->next;
		if (list && list->token && list->token->type == PIPE)
		{
			cmd[i]->pipe = 1;
			list = list->next;
		}
		ft_lstadd_back_alt(&p_list, ft_lstnew_alt(cmd[i]));
		i++;
	}
	cmd[i] = NULL;
	return (p_list);
}
