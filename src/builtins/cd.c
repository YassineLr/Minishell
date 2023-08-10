/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:40:49 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 23:54:18 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pwd(char *oldpwd, char *pwd)
{
	t_env	*t_oldpwd;
	t_env	*t_pwd;
	char	*tmp;

	t_pwd = search_in_env("PWD");
	tmp = t_pwd->value;
	if (t_pwd)
		t_pwd->value = pwd;
	free(tmp);
	t_oldpwd = search_in_env("OLDPWD");
	tmp = t_oldpwd->value;
	if (t_oldpwd)
		t_oldpwd->value = oldpwd;
	free(tmp);
}

char	*go_home(void)
{
	char	*home_path;

	if (search_in_env("HOME"))
	{
		home_path = ft_strdup(search_in_env("HOME")->value);
		if (home_path)
			chdir(home_path);
		return (home_path);
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_global.exitcode = 1;
		return (NULL);
	}
}

char	*go_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = NULL;
	if (search_in_env("OLDPWD"))
		oldpwd = ft_strdup(search_in_env("OLDPWD")->value);
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		g_global.exitcode = 1;
		return (NULL);
	}
	else
		chdir(oldpwd);
	return (oldpwd);
}

int	with_path(t_parser *parse, char *pwd, char *oldpwd)
{
	if (chdir(parse->command->cmds[1]) == 0)
		pwd = getcwd(pwd, 0);
	else
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		g_global.exitcode = 1;
		free(oldpwd);
		return (0);
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
		pwd = go_home();
	else if (!oldpwd)
	{
		g_global.exitcode = 255;
		perror("");
	}
	else if (!ft_strcmp(parse->command->cmds[1], "-"))
	{
		pwd = go_oldpwd();
		if (!pwd)
			return ;
	}	
	else if (!with_path(parse, pwd, oldpwd))
		return ;
	update_pwd(oldpwd, pwd);
}
