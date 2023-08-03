/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:16:46 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/03 01:58:18 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_utils(t_parser *parse)
{
	int	i;
	int	ext;

	i = 0;
	// while (parse->command->cmds[++i])
	// {
		if (!ft_atoi(parse->command->cmds[i]))
		{
			ft_putstr_fd("exit\nexit : numeric argument required\n",2);
			exitcode = 255;
			exit (exitcode);
		}
		else if (ft_atoi(parse->command->cmds[i]) && !parse->command->cmds[i + 1])
		{
			ext = ft_atoi(parse->command->cmds[i]);
			printf("exit\n");
			exit (ext);
		}
		else if (ft_atoi(parse->command->cmds[i]) && ft_atoi(parse->command->cmds[i + 1]))
		{
			ft_putstr_fd("exit : too many arguments\n", 2);
			return (-1);
		}
	// }
	return (1);
}

void	ft_exit(t_parser *parse)
{
	int	i;

	i = exit_utils(parse);
	if (i == 1)
	{
		ft_putstr_fd("exit\n", 1);
		exit(exitcode);
	}
}