/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:39:19 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 21:31:30 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_path(t_parser *parse, int i)
{
	char	*paths;
	char	**splited;
	char	*tmp;
	char	*path;

	paths = NULL;
	if (search_in_env("PATH"))
		paths = search_in_env("PATH")->value;
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
	return (NULL);
}

char	*ft_path(t_parser *parse)
{
	char	*path;
	char	*paths;
	int		i;

	i = 0;
	path = NULL;
	paths = NULL;
	if (parse->command->cmds[0])
	{
		if (parse->command->cmds[0][0] == '\0')
			command_nf_error(parse);
		else
			path = get_path(parse, 0);
	}
	return (path);
}

char	**env_in_tab(void)
{
	char	**envp;
	int		count;
	t_env	*cur;
	int		i;

	i = 0;
	count = 0;
	cur = g_global.env;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	envp = (char **) malloc ((count + 1) * sizeof (char *));
	cur = g_global.env;
	while (cur)
	{
		envp[i] = ft_strjoin(ft_strdup(cur->key), "=");
		envp[i] = ft_strjoin(envp[i], cur->value);
		cur = cur->next;
		i++;
	}
	envp[count] = NULL;
	return (envp);
}

void	in_child(t_parser *parse, t_parser *head, char **envt)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, ctrl_c_hdoc);
	if (parse->command->red_in == -1)
		exit(1);
	if (in_builtins(parse))
		red_buil(parse, 1);
	close_pipes(head, parse->command->pipe_fd.read,
		parse->command->pipe_fd.write);
	redirection(parse);
	execute_cmd(parse, envt);
}
