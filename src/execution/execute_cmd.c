/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:47:17 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/31 23:41:52 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

char    *ft_path(t_parser *parse, t_env *env)
{
	char    *path;
	char    *paths;
	char    **splited;
	int        i;

	i = 0;
	paths = NULL;
	if (search_in_env(env, "PATH"))
		paths = search_in_env(env, "PATH")->value;
	if (!paths)
	{
		printf("minishell: %s: No such file or directory\n", parse->command->cmds[0]);
		exit (127);
	}
	splited = ft_split(paths, ':');
	while (splited[i])
	{
		path = ft_strjoin(ft_strjoin(splited[i], "/"), parse->command->cmds[0]);
		if (access(path, X_OK | F_OK) == 0)
			return (path);
		i++;
	}
	// perror("");
	printf("%s: ",parse->command->cmds[0]);
	printf("command not found\n");
	exit(127);
	return (NULL);
}

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
	if (parse->command->pipe_fd.read)
		dup2(parse->command->pipe_fd.read, STDIN_FILENO);
	if (parse->command->pipe_fd.write != 1)
		dup2(parse->command->pipe_fd.write, STDOUT_FILENO);
	// if(parse->command->red_out != 1)
	// 		dup2(parse->command->red_out, STDOUT_FILENO);
	// if(parse->command->red_in != 0)
	// 		dup2(parse->command->red_in, STDIN_FILENO);
	// if (parse->command->pipe_fd.write != 1)
	// 	close(parse->command->pipe_fd.write);
	// if (parse->command->pipe_fd.to_close && parse->command->pipe_fd.to_close != 1)
	// 	close(parse->command->pipe_fd.to_close);
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
		envp[i] = ft_strjoin(envp[i], ft_strdup(cur->value));
		cur=cur->next;
		i++;
	}
	envp[count] = NULL;
	return(envp);
}

void set_pipes(t_parser *parse)
{
	t_parser     *courant;
	int            T[2];

	
	courant = parse;
	while (courant->next)
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
void	exit_status(int status)
{
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		exit(WTERMSIG(status) + 128);
	exit(0);
}

void   execute_cmd(t_parser *parse, t_env *env, char **envp)
{
	char *path;
	
	ft_dup(parse);
	execve(parse->command->cmds[0], parse->command->cmds, envp);
	path = ft_path(parse, env);
	if (!path)
		exit(127);
	if (execve(path, parse->command->cmds, envp) == -1)
	{
		write(2, "could not execve\n", 18);
		exit(127);
	}
	exit(1);
}

// void redirections(t_parser *parse)
// {
// 	if()
// }
// void close_files(t_parser *parse)
// {
// 	if(parse->command->red_in)
// }

void executor(t_parser *parse, t_env *env, char **envp)
{
	int 		pid;
	int			status;
	char 		**envt;
	t_parser	*head;
	
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
				if (in_builtins(parse))
					builtins(parse, env, 1);
				close_pipes(head,parse->command->pipe_fd.read,parse->command->pipe_fd.write);
				if (parse->command->red_in)
					dup2(parse->command->red_in, STDIN_FILENO);
				if (parse->command->red_out)
					dup2(parse->command->red_out, STDOUT_FILENO);
				execute_cmd(parse ,env , envt);
				if (parse->command->red_in)
					close(parse->command->red_in);
				if (parse->command->red_out != 1)
					close(parse->command->red_out);
			}
			parse = parse->next;
		}
		close_pipes(head, 0, 1);
		while(waitpid(-1, &status, 0) != -1);
	}
	// exit_status(status);
}