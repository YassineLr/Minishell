/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:16:46 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 02:54:13 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_utils(t_parser *parse)
{
	if (!parse->command->cmds[1])
	{
		ft_putstr_fd("exit\n", 1);
		g_global.exitcode = 0;
		exit (g_global.exitcode);
	}
	else if (!is_numeric(parse->command->cmds[1]))
	{
		ft_putstr_fd("exit\nexit : numeric argument required\n", 2);
		g_global.exitcode = 255;
		exit(g_global.exitcode);
		return (1);
	}
	else if (parse->command->cmds[1] && !parse->command->cmds[2])
	{
		g_global.exitcode = ft_atoi(parse->command->cmds[1]);
		ft_putstr_fd("exit\n", 1);
		exit (g_global.exitcode);
	}
	else if (ft_atoi(parse->command->cmds[1]) && parse->command->cmds[2])
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		return (-1);
	}
	return (1);
}

void	ft_exit(t_parser *parse)
{
	int	i;

	i = exit_utils(parse);
	if (i == 1)
	{
		ft_putstr_fd("exit\n", 1);
		exit(g_global.exitcode);
	}
}
