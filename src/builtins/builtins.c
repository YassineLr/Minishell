/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 02:17:20 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/16 03:25:15 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	invalid(char *str)
{
	int	i;

	i = 0;
	if (str[i] && !ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	in_builtins(t_parser *parse)
{
	if (parse->command->red_in == -1 || parse->command->red_in == -3)
		return (0);
	else if (parse->command->red_out == -1 || parse->command->red_out == -3)
		return (0);
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
