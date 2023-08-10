/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:16:46 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 23:07:28 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-' && str[i] != '+' && !ft_isdigit(str[i]))
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	check_max_min(char *s)
{
	unsigned long long	checker;
	int					i;
	int					sign;

	sign = 1;
	i = 0;
	while (s[i] == 32 || (s[i] <= 13 && s[i] >= 9))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] <= '9' && s[i] >= '0')
	{
		checker *= 10;
		checker = checker + s[i] - 48;
		i++;
	}
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
	if (strcmp(parse->command->cmds[1], "922337203685477580657") > 0)
		ext_err();
	else if (strcmp(parse->command->cmds[1], "-922337203685477580657") > 0
		&& ft_strlen(parse->command->cmds[1]) == ft_strlen("-922337203685477580657"))
		ext_err();
	if (parse->command->cmds[1] && !parse->command->cmds[2])
	{
		g_global.exitcode = ft_atoi(parse->command->cmds[1]);
		ft_putstr_fd("exit\n", 1);
		exit (g_global.exitcode);
	}
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
