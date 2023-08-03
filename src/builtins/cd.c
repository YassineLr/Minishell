/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylr <ylr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:40:49 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/04 00:19:18 by ylr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void update_pwd(t_env *env, char *oldpwd, char *pwd)
{
	t_env	*t_oldpwd;
	t_env	*t_pwd;

	t_pwd = search_in_env(env,"PWD");
	t_pwd->value = pwd;
	t_oldpwd = search_in_env(env,"OLDPWD");
	t_oldpwd->value = oldpwd;
}

void go_home(t_env *env)
{
	char	*home_path;

	home_path = search_in_env(env, "HOME")->value;
	if(home_path)
		chdir(home_path);
	else
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
}

char *go_oldpwd(t_env *env)
{
	char *oldpwd;
	
	oldpwd = search_in_env(env, "OLDPWD");
	if(!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return ;
	}
	else
		chdir(oldpwd);
	return(oldpwd);
}
void cd(t_parser *parse ,t_env *env)
{
	char *pwd=NULL;
	char *oldpwd= NULL;
	char *dir;

	dir = opendir(parse->command->cmds[0]);
	oldpwd = getcwd(oldpwd,0);
	if (!dir)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(dir, 2);
		perror(" ");
	}
	else
	{
	if(!parse->command->cmds[1] || !ft_strcmp(parse->command->cmds[1], "~"))
	{	
		go_home(env);
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
	}
	update_pwd(env, oldpwd, pwd);
}
// int		main(int ac, char **av)
// {
// 	char *pwd;
// 	char *usr;
	
// 	printf("%s\n", getcwd(pwd, 100));
	
// 	if(!av[1])
// 	{
		
// 		printf("%d",chdir("~"));
// 		printf("%s\n", getcwd(pwd, 100));
// 	}
// 	if(!chdir(av[1]))
// 		printf("%s\n", getcwd(pwd, 100));
// }