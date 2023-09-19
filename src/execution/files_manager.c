/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:37:43 by ylarhris          #+#    #+#             */
/*   Updated: 2023/09/19 18:49:46 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_files(t_parser *parse)
{
	if (parse->command->red_in)
		close(parse->command->red_in);
	if (parse->command->red_out != 1)
		close(parse->command->red_out);
}

void	execute_builtin(t_parser *parse, int child)
{
	int	save[2];

	save[0] = dup(0);
	save[1] = dup(1);
	redirection(parse);
	builtins(parse, child);
	ft_dup(save[0], STDIN_FILENO);
	ft_dup(save[1], STDOUT_FILENO);
	close_files(parse);
}

void	redirection(t_parser *parse)
{
	if (parse->command->red_in && parse->command->red_in != -1)
		ft_dup(parse->command->red_in, STDIN_FILENO);
	if (parse->command->red_out != 1)
		ft_dup(parse->command->red_out, STDOUT_FILENO);
}
