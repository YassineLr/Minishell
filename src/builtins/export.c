/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 03:49:34 by ylarhris          #+#    #+#             */
/*   Updated: 2023/07/19 10:11:55 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int key_exist(t_env *env, char **key_val)
{
    if(search_in_env(env,key_val[0]))
        return(1);
    return (0);
}

int invalid_identifier(char *str)
{
    int i;
    // int length;

    i = 0;
    while (str[i] && i < ft_strlen(str) - 1)
    {
        if(!(str[i] == '_' || ft_isalnum(str[i])))
            return(0);
        i++;
    }
    if(!(str[i] == '_' || ft_isalnum(str[i]) || str[i] == '+'))
            return(0);
    // if(str[i] != '+')
    //     return (0);
    return(1);
}
void concate_val(t_env *env, char **key_val)
{
    t_env   *to_concate;
    char    *new_identifier;
    // char    *new_value;
    
    new_identifier = ft_substr(key_val[0],0,ft_strlen(key_val[0])-1);
    // printf("id = %s\t , val : %s\n", new_identifier, key_val[1]);
    // exit(1);
    to_concate = search_in_env(env,new_identifier);
    printf("key => %s\t value => %s\n", to_concate->key, to_concate->value);
    if(to_concate)
    {
        // printf("this is the concat value : ==> %s",to_concate);
        if (index_at(key_val[0], '+') == ft_strlen(key_val[0])-1)
        {
            to_concate->key = new_identifier;
            to_concate->value = ft_strjoin(to_concate->value, key_val[1]);
        }
    }
}

char last_char(char *str)
{
    int i;

    i = 0;
    while(str[i+1])
        i++;
    return str[i];
}

void    export_no_args(t_env *env)
{
    t_env   *courant;

    courant = env;
    while (courant)
    {
        printf("%s=%s\n", courant->key, courant->value);
        courant = courant->next;
    }
}

void    export(t_parser *parse, t_env **env)
{
    char    **key_val;
    int     i = 1;

    key_val = malloc(2*sizeof(char*));
    if (!parse->command->cmds[1])
    {
        export_no_args(*env);
        return ;
    }    
    while (parse->command->cmds[i])
    {
        if(index_at(parse->command->cmds[i],'=') != -1 && index_at(parse->command->cmds[i],'='))
        {
            key_val[0] = ft_substr(parse->command->cmds[i], 0, index_at(parse->command->cmds[i],'='));
            key_val[1] = ft_strdup(ft_strchr(parse->command->cmds[i],'=')+1);
            // printf("%c %c\n", key_val[0][0],key_val[0][1]);
            if(!invalid_identifier(key_val[0]))
                ft_putstr_fd("invalid identifier\n",2);
            if(last_char(key_val[0]) == '+')
            {
                printf("concate\n");
                concate_val(*env, key_val);
            }
            else
            {
                if (key_exist(*env, key_val))
                    search_in_env(*env, key_val[0])->value = key_val[1];
                else
                    ft_lstadd_back_env(env,ft_lstnew_env(key_val));
            }
        }
        i++;
    }
}

// invalid identifier (alphanum + underscore)
// +=
// identifier (value is null && dont display in env but display in export)
// identifier= (is equal to idenyifier="" display in both)
// export j; exprt jj; export jjj
// export jjj; export jj; export j