/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:16:46 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/14 00:57:14 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_without(t_parser *parse)
{
	g_global.exitcode = ft_atoi(parse->command->cmds[1]);
	ft_putstr_fd("exit\n", 1);
	exit (g_global.exitcode);
}

void	ext_err(void)
{
	ft_putstr_fd("exit\nexit : numeric argument required\n", 2);
	g_global.exitcode = 255;
	exit(g_global.exitcode);
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
		ext_err();
	if (ft_strlen(parse->command->cmds[1]) > 21)
		ext_err();
	if (parse->command->cmds[1] && !parse->command->cmds[2])
		exit_without(parse);
	else if (ft_atoi(parse->command->cmds[1]))
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		g_global.exitcode = 1;
		return (-1);
	}
	return (1);
}

void	ft_exit(t_parser *parse)
{
	int	i;

	i = exit_utils(parse);
	if (!parse->command->cmds[1])
		exit(g_global.exitcode);
	if (i == 1)
	{
		ft_putstr_fd("exit\n", 1);
		exit(g_global.exitcode);
	}
}
