/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:04:21 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/09 02:50:46 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int    remove_firs(t_env **env, char *key)
{
    t_env *tmp;
    
    if (!ft_strcmp((*env)->key, key))
    {
        tmp = *env;
        if((*env)->next)
            *env = (*env)->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
        return(1);
    }
    return 0;
}
void    remove_variable(t_env **env, char *key)
{
    t_env   *precourant;
    t_env   *courant;
    
    if (!*env)
        return ;
    if (!(*env)->next)
    {
        free((*env)->key);
        free((*env)->value);
        *env = NULL;
    }
    else
    {
        courant = (*env)->next;
        precourant = *env;
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

void    unset(t_parser *parse, t_env *env)
{
    int i;
    
    exitcode = 0;
    i = 1;
    while (parse->command->cmds[i])
    {
        
        if(search_in_env(env, parse->command->cmds[i]))
            remove_variable(env, parse->command->cmds[i]);
        i++;
    }
}