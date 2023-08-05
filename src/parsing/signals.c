/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 08:52:30 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/04 14:19:03 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ctrl_c_handler(int signum)
// {
// 	printf("Received SIGINT (Ctrl+C).\n");
// 	rl_replace_line();
// 	exit(1);
// }
// void	ctrl_d_handler(int signum)
// {
// 	printf("Received EOF (Ctrl+D).\n");
// 	return ;
// }
// void	ctrl_backslash_handler(int signum)
// {
// 	printf("Received SIGQUIT (Ctrl+\\).\n");
// 	return ;
// }

int	signals_handler(char *line)
{
// 	signal(SIGINT, ctrl_c_handler);
// 	signal(EOF, ctrl_d_handler);
// 	signal(SIGQUIT, ctrl_backslash_handler);
	return (1);
}