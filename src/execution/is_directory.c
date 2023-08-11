/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 23:33:45 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/11 01:53:10 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	is_not_directory(t_parser *parse)
{
	ft_putstr_fd(parse->command->cmds[0], 2);
	ft_putstr_fd(" : is a directory\n", 2);
	g_global.exitcode = 126;
	exit(126);
}
