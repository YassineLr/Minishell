/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:04:21 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/09 21:05:37 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int count_env()
{
    int count;
    t_env *env;

    count = 0;
    if(global.env)
    {
        env = global.env;
        while (env)
        {
            count++;
            env = env->next;
        }
    }
    return (count);
}

int    remove_first(char *key)
{
    t_env *tmp;
    
    if (!ft_strcmp(global.env->key, key))
    {
        if(count_env() == 1)
        {
            ft_lstclear_env(&global.env,free);
            global.env = NULL;
        }
        else
        {
            tmp = global.env;
            if(global.env->next)
                global.env = global.env->next;
            free(tmp->key);
            free(tmp->value);
        }
        return(1);
    }
    return 0;
}
void    remove_variable(char *key)
{
    t_env   *precourant;
    t_env   *courant;
    int     check;
    
    if (!global.env)
        return ;
    check = remove_first(key);
    if(check)
        return ;
    else
    {
        courant = (global.env)->next;
        precourant = global.env;
        while (courant)
        {
            if(!ft_strcmp(courant->key,key))
            {
                precourant->next = courant->next;
                free(courant->key);
                free(courant->value);
                free(courant);
                return ;
            }
            precourant = precourant->next;
            courant = courant->next;
        }
    }
}

void    unset(t_parser *parse)
{
    int i;
    
    global.exitcode = 0;
    i = 1;
    while (parse->command->cmds[i])
    {
        if(!invalid_identifier(parse->command->cmds[i]))
            invalid_id_err();
        else if (search_in_env(parse->command->cmds[i]))
            remove_variable(parse->command->cmds[i]);
        i++;
    }
}