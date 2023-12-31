/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:32:03 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/14 19:56:45 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_args(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd[1], "-n", 2))
	{
		while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
		{
			j = 0;
			while (cmd[i][++j])
			{
				if (cmd[i][j] != 'n')
				{
					if (i == 1)
						return (i - 1);
					return (i);
				}
			}
			i++;
		}
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
