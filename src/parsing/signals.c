/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:52:30 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/10 02:00:38 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ctrl_c_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_global.exitcode = 1;
}

void	ctrl_c_hdoc(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit(1);
}

void	ctrl_d(void)
{
	ft_putstr_fd("exit\n", 2);
	exit(g_global.exitcode);
}

int	signals_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
	return (1);
}
