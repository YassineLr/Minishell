/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:32:03 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/09 03:47:31 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int args_treatment(char **cmd)
{
    int i;

    i = 1;
    if(!strcmp(cmd[1],"-n"))
    {
        while(!strcmp(cmd[i], "-n"))
            i++;
        return (i);
    }
    return (0);
}

void    ft_echo(t_parser *parse ,char *str)
{
    int     i;
    int     flag;

    flag = args_treatment(parse->command->cmds);
    i = flag;
    while(str[i])
    {
        write(1,str+i, 1);
        i++;
    }
    if(flag)
        write(1,"\n", 1);
}

// int main(int ac, char **av)
// {
//     ft_echo(av[1]);
// }