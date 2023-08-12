/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:40:49 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/11 23:02:46 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update(char *oldpwd, char *pwd)
{
	char	*tmp;

	if (search_in_env("PWD") && pwd)
	{
		tmp = search_in_env("PWD")->value;
		search_in_env("PWD")->value = ft_strdup(pwd);
		free(tmp);
	}
	if (search_in_env("OLDPWD") && oldpwd)
	{
		tmp = search_in_env("OLDPWD")->value;
		search_in_env("OLDPWD")->value = ft_strdup(oldpwd);
		free(tmp);
	}
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
		free(home_path);
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_global.exitcode = 1;
	}
}

void	go_oldpwd(char *oldpwd)
{
	char	*pwd;

	pwd = NULL;
	if (search_in_env("OLDPWD"))
	{
		pwd = ft_strdup(search_in_env("OLDPWD")->value);
		chdir(pwd);
		update(oldpwd, pwd);
		free(pwd);
	}
	else
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		g_global.exitcode = 1;
	}
}

void	with_path(t_parser *parse, char *pwd, char *oldpwd)
{
	if (chdir(parse->command->cmds[1]) == 0)
	{
		pwd = getcwd(pwd, 0);
		update(oldpwd, pwd);
		free(pwd);
	}
	else
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		g_global.exitcode = 1;
	}
	if (!oldpwd)
	{
		g_global.exitcode = 255;
		perror("");
	}
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
	else if (!ft_strcmp(parse->command->cmds[1], "-"))
		go_oldpwd(oldpwd);
	else
		with_path(parse, pwd, oldpwd);
	free(oldpwd);
}
