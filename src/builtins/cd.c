/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:40:49 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/05 09:59:48 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void update_pwd(t_env *env, char *oldpwd, char *pwd)
{
	t_env	*t_oldpwd;
	t_env	*t_pwd;

	t_pwd = search_in_env(env,"PWD");
	if(t_pwd)
		t_pwd->value = pwd;
	t_oldpwd = search_in_env(env,"OLDPWD");
	if(t_oldpwd)
		t_oldpwd->value = oldpwd;
}

void go_home(t_env *env)
{
	char	*home_path;

	if(search_in_env(env, "HOME"))
	{
		home_path = search_in_env(env, "HOME")->value;
		if(home_path)
			chdir(home_path);
	}
	else
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
}

char *go_oldpwd(t_env *env)
{
	char *oldpwd;
	
	oldpwd =NULL;
	if(search_in_env(env, "OLDPWD"))
		oldpwd = search_in_env(env, "OLDPWD")->value;
	if(!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return NULL;
	}
	else
		chdir(oldpwd);
	return(oldpwd);
}

void cd(t_parser *parse ,t_env *env)
{
	char *pwd=NULL;
	char *oldpwd= NULL;


	oldpwd = getcwd(oldpwd,0);
	if(!oldpwd)
		perror("");
	if(!parse->command->cmds[1] || !ft_strcmp(parse->command->cmds[1], "~"))
	{
		go_home(env);
		if(search_in_env(env, "HOME"))
			pwd = search_in_env(env, "HOME")->value;
	}
	else if(!ft_strcmp(parse->command->cmds[1], "-"))
	{
		pwd = go_oldpwd(env);
		if (!pwd)
			return ;
	}	
	else
	{
		if(chdir(parse->command->cmds[1]) == 0)
			pwd = getcwd(pwd,0);
		else
		{
			ft_putstr_fd("cd: No such file or directory\n",2);
			return ;
		}
	}
	update_pwd(env, oldpwd, pwd);
}