/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:47:17 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/04 06:42:51 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

char    *ft_path(t_parser *parse, t_env *env)
{
	char    *path;
	char    *paths;
	char    **splited;
	char 	*tmp;
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
			{
				no_path_err(parse);
				exit (exitcode);
			}
			splited = ft_split(paths, ':');
			while (splited[i])
			{
				tmp = ft_strjoin(splited[i], "/");
				path = ft_strjoin(tmp, parse->command->cmds[0]);
				if (access(path, X_OK | F_OK) == 0)
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
	execve(parse->command->cmds[0], parse->command->cmds, envp);
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

void	redirection(t_parser *parse)
{
	if (parse->command->red_in)
		dup2(parse->command->red_in, STDIN_FILENO);
	if (parse->command->red_out)
		dup2(parse->command->red_out, STDOUT_FILENO);
}

void	close_files(t_parser *parse)
{
	if (parse->command->red_in)
		close(parse->command->red_in);
	if (parse->command->red_out != 1)
		close(parse->command->red_out);
}

void in_child(t_parser *parse,t_parser *head, t_env *env ,char **envt)
{
	if (in_builtins(parse))
		builtins(parse, env, 1);
	close_pipes(head,parse->command->pipe_fd.read,parse->command->pipe_fd.write);
	redirection(parse);
	execute_cmd(parse ,env , envt);
}
void executor(t_parser *parse, t_env *env, char **envp)
{
	t_parser	*head;
	char 		**envt;
	int 		pid;
	int			status;
	
	head = parse;
	envt = env_in_tab(env);
	if (in_builtins(parse) && !parse->next)
		builtins(parse, env, 0);
	else
	{
		while (parse)
		{
			pid = fork();
			if(!pid)
			{
				if(parse->command->red_in != -1)
					in_child(parse, head, env, envt);
			}
			close_files(parse);
			parse = parse->next;
		}
		close_pipes(head, 0, 1);
		while(waitpid(-1, &status, 0) != -1)
			exit_status(status);
	}
	ft_free_strs(envt);
}
