/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 22:43:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/05 22:53:34 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_last_red_in(t_reds *red_ins)
{
	t_reds	*tmp;
	int		last_red;

	last_red = 0;
	tmp = red_ins;
	while (tmp->next)
	{
		close(tmp->fd);
		tmp = tmp->next;
	}
	if (tmp->fd == -2)
		last_red = -2;
	else
		last_red = tmp->fd;
	ft_lstclear_reds(&red_ins);
	return (last_red);
}

int	get_last_red_out(t_reds *red_outs)
{
	t_reds	*tmp;
	int		last_red;

	tmp = red_outs;
	while (red_outs->next)
	{
		close(red_outs->fd);
		red_outs = red_outs->next;
	}
	last_red = red_outs->fd;
	ft_lstclear_reds(&red_outs);
	return (last_red);
}

int	count_parser_words(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (is_redir(list->token->type))
			list = list->next;
		else if (list->token->type == PIPE)
			break ;
		else
		{
			if (list->token->expanded == 1 && list->token->in_quotes == 0)
				count += check_expanded_cmd(list->token->value);
			else
				count++;
		}
		list = list->next;
	}
	return (count);
}

int	check_expanded_cmd(char *str)
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

void	get_parser_word(t_list *list, char **cmds, int *i)
{
	int		j;
	char	**split;

	j = 0;
	if (list->token->value[0] == '\0')
	{
		cmds[*i] = ft_strdup("");
		*i += 1;
	}
	else if (list->token->expanded == 1 && list->token->in_quotes == 0)
	{
		j = 0;
		split = ft_split(list->token->value, ' ');
		while (split[j])
		{
			cmds[*i] = ft_strdup(split[j++]);
			*i += 1;
		}
		ft_free_strs(split);
	}
	else
	{
		cmds[*i] = ft_strdup(list->token->value);
		*i += 1;
	}
}
