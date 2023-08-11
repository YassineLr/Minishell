/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:40:49 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/11 07:28:08 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void update(char *oldpwd, char *pwd)
{
	if(search_in_env("PWD"))
		search_in_env("PWD")->value = ft_strdup(pwd);
	if(search_in_env("OLDPWD"))
		search_in_env("OLDPWD")->value = ft_strdup(oldpwd);
}

void	go_home(char *oldpwd)
{
	char	*home_path;

	if (search_in_env("HOME"))
	{
		home_path = ft_strdup(search_in_env("HOME")->value);
		if (home_path)
			chdir(home_path);
		update(oldpwd, home_path);
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_global.exitcode = 1;
	}
}

int	with_path(t_parser *parse, char *pwd, char *oldpwd)
{
	if (chdir(parse->command->cmds[1]) == 0)
	{
		pwd = getcwd(pwd, 0);
		update(oldpwd, pwd);
	}
	else
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		g_global.exitcode = 1;
		free(oldpwd);
		return (1);
	}
	free(pwd);
	return (1);
}

void	cd(t_parser *parse)
{
	char	*pwd;
	char	*oldpwd;

	pwd = NULL;
	oldpwd = NULL;
	g_global.exitcode = 0;
	oldpwd = getcwd(oldpwd, 0);
	if (!parse->command->cmds[1] || !ft_strcmp(parse->command->cmds[1], "~"))
		go_home(oldpwd);
	else if (!oldpwd)
	{
		g_global.exitcode = 255;
		perror("");
	}
	else if (with_path(parse, pwd, oldpwd))
		return ;
}