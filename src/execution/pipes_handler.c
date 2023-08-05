/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:53:36 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/05 15:18:53 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

void init_fds(t_parser *parse)
{
	t_parser    *cur;

	cur = parse;
	while (cur)
	{
		cur->command->pipe_fd.read = 0;
		cur->command->pipe_fd.write = 1;
		cur = cur->next;
	}
}

void    ft_dup(t_parser *parse)
{
	close_pipes(parse, parse->command->pipe_fd.read, parse->command->pipe_fd.write);
	if (parse->command->pipe_fd.read && !parse->command->red_in)
		dup2(parse->command->pipe_fd.read, STDIN_FILENO);
	if (parse->command->pipe_fd.write != 1)
		dup2(parse->command->pipe_fd.write, STDOUT_FILENO);
}

void set_pipes(t_parser *parse)
{
	t_parser     *courant;
	int            T[2];

	
	courant = parse;
	while (courant && courant->next)
	{
		if (courant->command->pipe == 1)
		{
			pipe(T);
			courant->command->pipe_fd.write = T[1];
			courant->next->command->pipe_fd.read = T[0];
		}
		courant = courant->next;
	}
}


void	close_pipes(t_parser *parse, int fread, int fwrite)
{
	t_parser	*cur;

	cur = parse;
	
	while (cur)
	{
		if(cur->command->pipe_fd.write != fwrite && cur->command->pipe_fd.write != 1)
			close(cur->command->pipe_fd.write);	
		if(cur->command->pipe_fd.read != fread && cur->command->pipe_fd.read)
				close(cur->command->pipe_fd.read);
		cur = cur->next;
	}
}