/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 02:07:17 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 02:42:44 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd(void)
{
	char	*pwd;

	pwd = NULL;
	g_global.exitcode = 0;
	pwd = getcwd(pwd, 0);
	if (pwd)
		ft_putendl_fd(pwd, 1);
	free(pwd);
}
