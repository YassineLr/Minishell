/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:07:48 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/14 00:01:59 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_lexer(t_lexer *lexer)
{
	if (!lexer)
		return ;
	free(lexer->content);
	free(lexer);
	lexer = 0;
}

void	free_plist(t_parser **list)
{
	int			i;
	t_parser	*tmp;

	i = 0;
	tmp = 0;
	if (!*list)
		return ;
	while (*list)
	{
		i = -1;
		while ((*list)->command->cmds[++i])
			free((*list)->command->cmds[i]);
		free((*list)->command->cmds[i]);
		free((*list)->command->cmds);
		free((*list)->command);
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	*list = 0;
}

void	free_list(t_list **list)
{
	ft_lstclear(list, &free);
	list = 0;
}

void	free_hdc(t_hdc *hdc)
{
	if (!hdc)
		return ;
	if (hdc->fds)
		free(hdc->fds);
	free(hdc);
}

void	free_cmds(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd)
	{
		if (cmd->cmds)
		{
			while (cmd->cmds[++i])
				free(cmd->cmds[i]);
			free(cmd->cmds);
		}
		free(cmd);
	}
}
