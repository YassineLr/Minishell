/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 02:17:20 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/09 21:26:48 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	in_builtins(t_parser *parse)
{
	if (!ft_strcmp(parse->command->cmds[0], "echo"))
		return (1);
	else if (!ft_strcmp(parse->command->cmds[0], "cd"))
		return (1);
	else if (!ft_strcmp(parse->command->cmds[0], "export"))
		return (1);
	else if (!ft_strcmp(parse->command->cmds[0], "pwd"))
		return (1);
	else if (!ft_strcmp(parse->command->cmds[0], "env"))
		return (1);
	else if (!ft_strcmp(parse->command->cmds[0], "unset"))
		return (1);
	else if (!ft_strcmp(parse->command->cmds[0], "exit"))
		return (1);
	return (0);
}

void	builtins(t_parser *parse, int child)
{
	if (child)
		ft_dup(parse);
	if (!ft_strcmp(parse->command->cmds[0], "echo"))
		ft_echo(parse);
	else if (!ft_strcmp(parse->command->cmds[0], "cd"))
		cd(parse);
	else if (!ft_strcmp(parse->command->cmds[0], "export"))
		export(parse);
	else if (!ft_strcmp(parse->command->cmds[0], "pwd"))
		pwd();
	else if (!ft_strcmp(parse->command->cmds[0], "env"))
		ft_env();
	else if (!ft_strcmp(parse->command->cmds[0], "unset"))
		unset(parse);
	else if (!ft_strcmp(parse->command->cmds[0], "exit"))
		ft_exit(parse);
	if (child)
		exit(0);
}
