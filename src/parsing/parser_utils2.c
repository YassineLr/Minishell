/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 02:54:08 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/11 02:54:54 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	append(t_list **list, t_reds **r_outs)
{
	int	fd;

	fd = 0;
	*list = (*list)->next;
	if (*list && (*list)->token)
	{
		fd = open_append(*list);
		if (fd == -1 || fd == -3)
		{
			ft_lstadd_back_reds(r_outs, ft_lstnew_reds(-1));
			return (0);
		}
		ft_lstadd_back_reds(r_outs, ft_lstnew_reds(fd));
	}
	return (1);
}

int	red_out(t_list **list, t_reds **r_outs, int type)
{
	int	fd;

	fd = 0;
	if (type == RED_OUT)
	{
		*list = (*list)->next;
		if (*list && (*list)->token)
		{
			fd = open_redout((*list));
			if (fd == -1 || fd == -3)
			{
				ft_lstadd_back_reds(r_outs, ft_lstnew_reds(-1));
				return (0);
			}
			ft_lstadd_back_reds(r_outs, ft_lstnew_reds(fd));
		}
	}
	else if (type == APPEND)
		return (append(list, r_outs));
	return (1);
}

int	red_in(t_list **list, t_reds **r_ins, int type)
{
	int	fd;

	fd = 0;
	if (type == RED_IN)
	{
		*list = (*list)->next;
		if (*list && (*list)->token)
		{
			fd = open_redin((*list));
			if (fd == -1 || fd == -3)
			{
				ft_lstadd_back_reds(r_ins, ft_lstnew_reds(-1));
				return (0);
			}
			ft_lstadd_back_reds(r_ins, ft_lstnew_reds(fd));
		}
	}
	else if (type == HEREDOC)
	{
		*list = (*list)->next;
		if (*list && (*list)->token)
			ft_lstadd_back_reds(r_ins, ft_lstnew_reds(-2));
	}
	return (1);
}

void	get_last_reds(t_reds *r_outs, t_reds *r_ins, t_redir *reds)
{
	if (r_outs)
		reds->red_out = get_last_red_out(r_outs);
	else
		reds->red_out = 1;
	if (r_ins)
		reds->red_in = get_last_red_in(r_ins);
	else
		reds->red_in = 0;
}
