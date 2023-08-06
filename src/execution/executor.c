/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:47:17 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/06 18:30:11 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

char    *ft_path(t_parser *parse, t_env *env)
{
	char    *path;
	char    *paths;
	char    **splited;
	char	*tmp;
	int        i;

	i = 0;
	paths = NULL;
	if(parse->command->cmds[0])
	{
		if(parse->command->cmds[0][0] == '\0')
			command_nf_error(parse);
		else
		{
			if (search_in_env(env, "PATH"))
				paths = search_in_env(env, "PATH")->value;
			if (!paths)
				no_path_err(parse);
			splited = ft_split(paths, ':');
			while (splited[i])
			{
				tmp = ft_strjoin(splited[i], "/");
				path = ft_strjoin(tmp, parse->command->cmds[0]);
				if (access(path, F_OK) == 0)
					return (path);
				i++;
			}
			command_nf_error(parse);
		}
	}
	return (NULL);
}

char **env_in_tab(t_env *env)
{
	char    **envp;
	int     count;
	t_env   *cur;
	int     i;
	
	i = 0;
	count = 0;
	cur = env;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	envp = (char **) malloc((count+1)*sizeof(char *));
	cur = env;
	while (cur)
	{
		envp[i] = ft_strjoin(ft_strdup(cur->key),"=");
		envp[i] = ft_strjoin(envp[i], cur->value);
		cur=cur->next;
		i++;
	}
	envp[count] = NULL;
	return(envp);
}

void	exit_status(int status)
{
	if (WIFEXITED(status))
		exitcode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exitcode = WTERMSIG(status) + 128;
}

void   execute_cmd(t_parser *parse, t_env *env, char **envp)
{
	char *path;
	
	exitcode = 0;
	ft_dup(parse);
	if(index_at(parse->command->cmds[0],'/') != -1)
	{
		if(access(parse->command->cmds[0], X_OK) == 0)
			execve(parse->command->cmds[0],parse->command->cmds,envp);
		else
		{
			ft_putstr_fd("minishell: no such file or directory\n", 2);
			exitcode = 127;
			exit(exitcode);
		}
	}
	path = ft_path(parse, env);
	if (!path)
	{
		exitcode = 127;
		exit(exitcode);
	}
	if (parse->command->cmds[0])
		if (execve(path, parse->command->cmds, envp) == -1)
		{
			print_error("could not execve\n");
			exitcode = 127;
			exit(exitcode);
		}
	exit(exitcode);
}

void ftt_dup(int fildes, int fildes2)
{
	dup2(fildes,fildes2);
	close(fildes);
}

void	redirection(t_parser *parse)
{
	if (last_redin(parse->command->red_in) != -2)
		ftt_dup(last_redin(parse->command->red_in), STDIN_FILENO);
	else if (last_redin(parse->command->red_in) == -2)
		ftt_dup(parse->command->red_in->hdoc->in, STDIN_FILENO);
	if (parse->command->red_out != 1)
		ftt_dup(parse->command->red_out, STDOUT_FILENO);
}

void	close_files(t_parser *parse)
{
	if (last_redin(parse->command->red_in) != -2 && parse->command->red_in)
		close(last_redin(parse->command->red_in));
	if (parse->command->red_out != 1)
		close(parse->command->red_out);
}


void red_buil(t_parser *parse, t_env *env, int child)
{
	int save[2];

	save[0] = dup(0);
	save[1] = dup(1);
	redirection(parse);
	builtins(parse, env, child);
	ftt_dup(save[0],STDIN_FILENO);
	ftt_dup(save[1], STDOUT_FILENO);
	close_files(parse);
}

void in_child(t_parser *parse,t_parser *head, t_env *env ,char **envt)
{
	// if (!parse->command->red_in)
	// 	exit(1);
	if (in_builtins(parse))
		red_buil(parse, env, 1);
	hdoc(parse, env);
	close_pipes(head,parse->command->pipe_fd.read,parse->command->pipe_fd.write);
	redirection(parse);
	execute_cmd(parse ,env ,envt);
}

void executor(t_parser *parse, t_env *env, char **envp)
{
	t_parser	*head;
	char 		**envt;
	int 		pid;
	int			status;
	
	head = parse;
	envt = env_in_tab(env);
	if (head && in_builtins(parse) && !head->next)
		red_buil(parse, env, 0);
	else
	{
		while (parse)
		{
			pid = fork();
			if(!pid)
				in_child(parse, head, env, envt);
			close_files(parse);
			parse = parse->next;
		}
		close_pipes(head, 0, 1);
		while(waitpid(-1, &status, 0) != -1)
			exit_status(status);
	}
	ft_free_strs(envt);
	// exit(1);
}
