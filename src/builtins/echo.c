/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:32:03 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 02:42:16 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_args(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd[1], "-n"))
	{
		while (!ft_strcmp(cmd[i], "-n"))
			i++;
		return (i);
	}
	return (0);
}

void	ft_echo(t_parser *parse)
{
	int		i;
	int		flag;

	g_global.exitcode = 0;
	flag = 0;
	if (parse->command->cmds[1])
	{
		flag = check_args(parse->command->cmds);
		if (flag)
			i = flag;
		else
			i = 1;
		while (parse->command->cmds[i])
		{
			ft_putstr_fd(parse->command->cmds[i], 1);
			if (parse->command->cmds[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if (!flag)
		write(1, "\n", 1);
}
