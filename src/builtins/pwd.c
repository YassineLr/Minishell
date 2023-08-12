/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 02:07:17 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/11 23:03:49 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd(void)
{
	char	*pwd;

	pwd = NULL;
	g_global.exitcode = 0;
	if (search_in_env("PWD"))
	{
		ft_putendl_fd(search_in_env("PWD")->value, 1);
	}
	else
	{
		pwd = getcwd(pwd, 0);
		if (pwd)
			ft_putendl_fd(pwd, 1);
		free(pwd);
	}
}
