/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:08:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/01 08:59:05 by oubelhaj         ###   ########.fr       */
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

int	check_first_cmd(char *str)
{
	int		count;
	char	**split;

	split = ft_split(str, ' ');
	count = ft_count_strs(split);
	ft_free_strs(split);
	if (count == 0)
		return (1);
	return (count);
}

int	count_words(t_list *list)
{
	int	first;
	int	count;

	first = 1;
	count = 0;
	while (list)
	{
		if (list->token->type == RED_IN || list->token->type == RED_OUT
			|| list->token->type == APPEND || list->token->type == HEREDOC)
			list = list->next;
		else if (list->token->type == PIPE)
			break;
		else
		{
			if (first == 1 && list->token->expanded == 1)
			{
				count += check_first_cmd(list->token->value);
				first = 0;
			}
			else
				count++;
			first = 0;
		}
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
				ft_lstadd_back_reds(&red_outs, ft_lstnew_reds(open_redout(list)));
		}
		else if (list->token->type == APPEND)
		{
			list = list->next;
			if (list && list->token)
				ft_lstadd_back_reds(&red_outs, ft_lstnew_reds(open_append(list)));
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
	t_reds	*tmp;
	t_reds	*red_ins;
	int		last_red;

	last_red = 0;
	red_ins = NULL;
	tmp = NULL;
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
				ft_lstadd_back_reds(&red_ins, ft_lstnew_reds(open_redin(list)));
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
		tmp = red_ins;
		while (tmp->next)
		{
			close(tmp->fd);
			tmp = tmp->next;
		}
		if (tmp->fd == -2)
		{
			if (is_last_hc(list))
				last_red = -2;
			else
				last_red = -1;
			ft_lstclear_reds(&red_ins);
		}
		else
		{
			last_red = red_ins->fd;
			ft_lstclear_reds(&red_ins);
		}
	}
	return (last_red);
}

char	**get_cmds(t_list *list)
{
	int		i;
	int		j;
	char	**split;
	int		first;
	int		count;
	char	**cmds;

	i = 0;
	j = 0;
	first = 1;
	split = NULL;
	count = count_words(list);
	if (count == 0)
		return (NULL);
	cmds = malloc(sizeof(char *) * (count + 1));
	while (list)
	{
		if (list->token->type == RED_IN || list->token->type == RED_OUT || list->token->type == APPEND
			|| list->token->type == HEREDOC)
			list = list->next;
		else if (list->token->type == PIPE)
			break;
		else if (list->token->type == WORD)
		{
			if (list->token->value[0] == '\0')
			{
				cmds[i] = ft_strdup("");
				i++;
			}
			else if (first == 1 && list->token->expanded == 1 && list->token->in_quotes == 0)
			{
				j = 0;
				split = ft_split(list->token->value, ' ');
				while (split[j])
				{
					cmds[i] = ft_strdup(split[j]);
					j++;
					i++;
				}
				ft_free_strs(split);
			}
			else
			{
				cmds[i] = ft_strdup(list->token->value);
				i++;
			}
			first = 0;
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

	i = 0;
	p_list = NULL;
	cmd = malloc(sizeof(char *) * (count_cmds(list) + 1));
	if (!cmd)
		return (NULL);
	while (list)
	{
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
		ft_free_strs(cmd[i]->cmds);
		cmd[i]->cmds = NULL;
		i++;
	}
	cmd[i] = NULL;
	i = -1;
	while (cmd[++i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
	}
	free(cmd);
	cmd = NULL;
	return (p_list);
}
