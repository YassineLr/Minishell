/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 02:07:17 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/09 18:08:09 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void pwd(void)
{
    char *pwd = NULL;


    global.exitcode = 0;
    pwd = getcwd(pwd, 0);
    if(pwd)
        printf("%s\n", pwd);
    free(pwd);
}
