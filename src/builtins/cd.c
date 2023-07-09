/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:40:49 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/09 03:13:45 by ylarhris         ###   ########.fr       */
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
	chdir(home_path);
}

void cd(t_parser *parse ,t_env *env)
{
	char *pwd=NULL;
	char *oldpwd= NULL;
	// char *usr;
	// int i;
	
	oldpwd = getcwd(oldpwd,0);
	if(!parse->command->cmds[1])
	{	
		go_home(env);
		pwd = search_in_env(env, "HOME")->value;
	}
	else
	{
		if(chdir(parse->command->cmds[1]) == 0)
			pwd = getcwd(pwd,0);
		else
		{
			ft_putstr_fd("cd: No such file or directory",2);
		}
	}
	update_pwd(env, oldpwd, pwd);
	printf("oldpwd : [%s] | pwd : [%s]\n", search_in_env(env,"OLDPWD")->value, search_in_env(env,"PWD")->value);
	printf("in the end : %s\n", getcwd(pwd, 100));
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