/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 03:49:34 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/09 23:07:57 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    export(t_parser *parse, t_env *env)
{
    char    **key_val;
    int     i = 1;

    key_val = malloc(2*sizeof(char*));
    while (parse->command->cmds[i])
    {
        if(index_at(parse->command->cmds[i],'=') != -1 && index_at(parse->command->cmds[i],'='))
        {
            key_val[0] = ft_strdup(ft_substr(parse->command->cmds[i], 0, index_at(parse->command->cmds[i],'=')));
            key_val[1] = ft_strdup(ft_strchr(parse->command->cmds[i],'=')+1);
            ft_lstadd_back_env(&env,ft_lstnew_env(key_val));
        }
        i++;
    }
}