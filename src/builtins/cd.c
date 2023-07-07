/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:40:49 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/07 03:53:06 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void home_red()
void cd(t_parser *parse)
{
	char *wd;
	char *usr;
	
	printf("%s\n", getcwd(pwd, 100));
	
	if(!av[1])
	{
		printf("%d",chdir("~"));
		printf("%s\n", getcwd(pwd, 100));
	}

}
int		main(int ac, char **av)
{
	char *wd;
	char *usr;
	
	printf("%s\n", getcwd(pwd, 100));
	
	if(!av[1])
	{
		
		printf("%d",chdir("~"));
		printf("%s\n", getcwd(pwd, 100));
	}
// 	if(!chdir(av[1]))
// 		printf("%s\n", getcwd(pwd, 100));
}