/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:40:49 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/09 22:01:43 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd(char *oldpwd, char *pwd)
{
	t_env	*t_oldpwd;
	t_env	*t_pwd;

	t_pwd = search_in_env("PWD");
	if (t_pwd)
		t_pwd->value = pwd;
	t_oldpwd = search_in_env("OLDPWD");
	if (t_oldpwd)
		t_oldpwd->value = oldpwd;
}

void	go_home(void)
{
	char	*home_path;

	if (search_in_env("HOME"))
	{
		home_path = search_in_env("HOME")->value;
		if (home_path)
			chdir(home_path);
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		global.exitcode = 1;
	}
}

char	*go_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = NULL;
	if (search_in_env("OLDPWD"))
		oldpwd = search_in_env("OLDPWD")->value;
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		global.exitcode = 1;
		return (NULL);
	}
	else
		chdir(oldpwd);
	return (oldpwd);
}

void	cd(t_parser *parse)
{
	char	*pwd;
	char	*oldpwd;

	pwd = NULL;
	oldpwd = NULL;
	global.exitcode = 0;
	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
	{
		global.exitcode = 255;
		perror("");
	}
	if (!parse->command->cmds[1] || !ft_strcmp(parse->command->cmds[1], "~"))
	{
		go_home();
		if (search_in_env("HOME"))
			pwd = search_in_env("HOME")->value;
	}
	else if (!ft_strcmp(parse->command->cmds[1], "-"))
	{
		pwd = go_oldpwd();
		if (!pwd)
			return ;
	}	
	else
	{
		if (chdir(parse->command->cmds[1]) == 0)
			pwd = getcwd(pwd, 0);
		else
		{
			ft_putstr_fd("cd: No such file or directory\n", 2);
			global.exitcode = 1;
			return ;
		}
	}
	update_pwd(oldpwd, pwd);
}
