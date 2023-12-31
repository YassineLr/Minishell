/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:56:06 by ylarhris          #+#    #+#             */
/*   Updated: 2023/09/19 18:44:47 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	command_nf_error(t_parser *parse)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(parse->command->cmds[0], 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd("command not found\n", 2);
	g_global.exitcode = 127;
}

void	print_error(char *error)
{
	ft_putstr_fd(error, 2);
	g_global.exitcode = 127;
}

void	exit_with_err(void)
{
	g_global.exitcode = 127;
	exit(g_global.exitcode);
}

void	no_path_err(t_parser *parse)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(parse->command->cmds[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_global.exitcode = 127;
	exit (g_global.exitcode);
}
