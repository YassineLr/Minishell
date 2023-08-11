/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:40:49 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/11 05:20:23 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd(char *oldpwd, char *pwd)
{
	t_env	*t_oldpwd;
	t_env	*t_pwd;
	char	*tmp;

	t_pwd = search_in_env("PWD");
	t_pwd = search_in_env("OLDPWD");
	if (t_pwd || pwd || t_pwd->value)
	{
		tmp = t_pwd->value;
		t_pwd->value = pwd;
		free(tmp);	
	}
	if(t_oldpwd || oldpwd || t_oldpwd->value)
	{
		t_oldpwd = search_in_env("OLDPWD");
		tmp = t_oldpwd->value;
		t_oldpwd->value = oldpwd;
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
		update_pwd(oldpwd, home_path);
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
		pwd = getcwd(pwd, 0);
	else
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		g_global.exitcode = 1;
		// free(oldpwd);
		return (0);
	}
	update_pwd(oldpwd, pwd);
	// free(pwd);
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
		return ;
	}
	else if (with_path(parse, pwd, oldpwd))
		return ;
}