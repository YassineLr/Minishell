/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:47:17 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/09 22:03:08 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_status(int status)
{
	if (WIFEXITED(status))
		global.exitcode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		global.exitcode = WTERMSIG(status) + 128;
}

void	execute_cmd(t_parser *parse, char **envp)
{
	char	*path;

	global.exitcode = 0;
	ft_dup(parse);
	if (index_at(parse->command->cmds[0], '/') != -1)
	{
		if (access(parse->command->cmds[0], X_OK) == 0)
			execve(parse->command->cmds[0], parse->command->cmds, envp);
		else
		{
			ft_putstr_fd("minishell: no such file or directory\n", 2);
			global.exitcode = 127;
			exit(global.exitcode);
		}
	}
	path = ft_path(parse);
	if (!path)
	{
		global.exitcode = 127;
		exit(global.exitcode);
	}
	if (parse->command->cmds[0]
		&& (execve(path, parse->command->cmds, envp) == -1))
	{
		print_error("could not execve\n");
		global.exitcode = 127;
		exit(global.exitcode);
	}
	exit(global.exitcode);
}

void	executor(t_parser *parse, char **envp)
{
	t_parser	*head;
	char		**envt;
	int			pid;
	int			status;

	head = parse;
	if (head && in_builtins(parse) && !head->next)
		red_buil(parse, 0);
	else
	{
		envt = env_in_tab();
		while (parse)
		{
			pid = fork();
			if (!pid)
				in_child(parse, head, envt);
			close_files(parse);
			parse = parse->next;
		}
		close_pipes(head, 0, 1);
		while (waitpid(-1, &status, 0) != -1)
			exit_status(status);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			printf("Quit: %d\n", WTERMSIG(status));
		ft_free_strs(envt);
	}
}
