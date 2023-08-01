/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylr <ylr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:16:46 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/01 19:16:12 by ylr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit_2(t_parser *parse)
{
	int	i;
	int	ext;

	i = 0;
	while (parse->command->cmds[++i])
	{
		if (!ft_atoi(parse->command->cmds[i]))
		{
			printf("exit\nexit : numeric argument required\n");
			exitcode = 255;
			exit (exitcode);
		}
		else if (ft_atoi(parse->command->cmds[i]) && !parse->command->cmds[i + 1])
		{
			ext = ft_atoi(parse->command->cmds[i]);
			exit (ext);
		}
		else if (ft_atoi(parse->command->cmds[i]) && ft_atoi(parse->command->cmds[i + 1]))
		{
			ft_error("exit : too many arguments\n", 1);
			return (-1);
		}
	}
	return (i);
}

void	ft_exit(t_parser *parse)
{
	int	i;

	i = ft_exit_2(parse);
	if (i == 1)
	{
		printf("exit\n");
		exit(exitcode);
	}
}