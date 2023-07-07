/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:32:03 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/07 02:27:51 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int args_treatment(char **cmd)
{
    int i;

    i = 0;
    if(strcmp(cmd[1]))
    {
        while(!strcmp(cmd->cmds[i], "-n"))
        {
            i++;
        }
    }
}

void    ft_echo(char *str)
{
    int     i;

    i = 0;
    while(str[i])
    {
        write(1,str+i, 1);
        i++;
    }
        write(1,"\n", 1);
}

int main(int ac, char **av)
{
    ft_echo(av[1]);
}