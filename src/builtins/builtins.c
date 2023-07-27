/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 02:17:20 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/27 23:57:40 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int in_builtins(t_parser *parse)
{
    if(!ft_strcmp(parse->command->cmds[0], "echo"))
        return 1;
    else if(!ft_strcmp(parse->command->cmds[0], "cd"))
        return 1;
    else if(!ft_strcmp(parse->command->cmds[0], "export"))
        return 1;
    else if(!ft_strcmp(parse->command->cmds[0], "pwd"))
        return 1;
    else if(!ft_strcmp(parse->command->cmds[0], "env"))
        return 1;
    else if(!ft_strcmp(parse->command->cmds[0], "unset"))
        return 1;
    return 0;
}

void builtins(t_parser *parse, t_env *env, int child)
{
    if(child)
        ft_dup(parse);
    if(!ft_strcmp(parse->command->cmds[0], "echo"))
        ft_echo(parse);
    else if(!ft_strcmp(parse->command->cmds[0], "cd"))
        cd(parse, env);
    else if(!ft_strcmp(parse->command->cmds[0], "export"))
        export(parse, &env);
    else if(!ft_strcmp(parse->command->cmds[0], "pwd"))
        pwd();
    else if(!ft_strcmp(parse->command->cmds[0], "env"))
        ft_env(env);
    else if(!ft_strcmp(parse->command->cmds[0], "unset"))
        unset(parse, env);
    if(child)
        exit(0);
}
