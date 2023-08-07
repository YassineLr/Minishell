/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:52:30 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/06 19:28:33 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ctrl_c_handler(int signum)
// {
// 	(void)signum;
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	ctrl_d_handler(int signum)
// {
// 	(void)signum;
// if (signum == SIGQUIT)
    // printf("Q")
// 	ft_putstr_fd("exit\n", 1);
// 	exit(exitcode);
// }

// void	ctrl_backslash_handler(int signum)
// {
// 	signal(SIGINT, SIG_IGN);
	
// }

// int	signals_handler()
// {
// 	signal(SIGINT, ctrl_c_handler);
// 	signal(SIGQUIT, ctrl_backslash_handler);
// 	return (1);
// }