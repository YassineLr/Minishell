/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:47:17 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/14 00:20:52 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_status(int status)
{
	if (WIFEXITED(status))
		g_global.exitcode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global.exitcode = WTERMSIG(status) + 128;
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		printf("Quit: %d\n", WTERMSIG(status));
}

void	exit_with_err(void)
{
	g_global.exitcode = 127;
	exit(g_global.exitcode);
}

void	run_script(t_parser *parse, char **envp)
{
	if (access(parse->command->cmds[0], X_OK) == 0)
		execve(parse->command->cmds[0], parse->command->cmds, envp);
	else
	{
		perror("");
		g_global.exitcode = 127;
		if (access(parse->command->cmds[0], X_OK) == -1)
			g_global.exitcode = 126;
		exit(g_global.exitcode);
	}
}

void	execute_cmd(t_parser *parse, char **envp)
{
	char		*path;

	if (parse->command->red_in != -1 && parse->command->red_out != -1)
	{
		g_global.exitcode = 0;
		ft_dup(parse);
		if (is_directory(parse->command->cmds[0]) == 1)
			is_not_directory(parse);
		if (index_at(parse->command->cmds[0], '/') != -1)
			run_script(parse, envp);
		path = ft_path(parse);
		if (!path)
			exit_with_err();
		if (parse->command->cmds[0]
			&& (execve(path, parse->command->cmds, envp) == -1))
		{
			print_error("could not execve\n");
			exit_with_err();
		}
	}
	exit(g_global.exitcode);
}

void	executor(t_parser *parse)
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
			if (parse->command->cmds && parse->command->cmds[0])
			{
				pid = fork();
				if (!pid)
					in_child(parse, head, envt);
				close_files(parse);
			}
			parse = parse->next;
		}
		close_pipes(head, 0, 1);
		while (waitpid(-1, &status, 0) != -1)
			exit_status(status);
		ft_free_strs(envt);
	}
}
