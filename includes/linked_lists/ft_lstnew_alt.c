/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_alt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 05:34:59 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/25 23:08:29 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_parser	*ft_lstnew_alt(t_cmd *cmd)
{
	int			i;
	t_parser	*node;

	i = -1;
	node = malloc(sizeof(t_parser));
	if (!node)
		return (0);
	node->command = init_cmd();
	node->command->cmds = malloc(sizeof(char *) * (ft_count_strs(cmd->cmds) + 1));
	if (ft_count_strs(cmd->cmds) == 0)
		node->command->cmds[0] = NULL;
	else
	{
		while (cmd->cmds[++i])
			node->command->cmds[i] = ft_strdup(cmd->cmds[i]);
		node->command->cmds[i] = NULL;
	}
	node->command->pipe = cmd->pipe;
	node->command->red_in = cmd->red_in;
	node->command->red_out = cmd->red_out;
	node->next = NULL;
	return (node);
}
