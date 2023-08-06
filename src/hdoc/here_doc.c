/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:48:38 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/06 16:16:17 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int last_redin(t_reds *red)
{
    t_reds  *cur;

    cur = red;
    while (cur)
    {
        if(!cur->next)
            return(cur->fd);
        cur = cur->next;
    }
    return(0);
}

void set_hdoc_pipes(t_parser *parse)
{
    int i;
    int t[2];
    t_reds *cur;

    if(last_redin(parse->command->red_in) == -2)
    {
        pipe(t);
        cur->hdoc->in = t[1];
        cur->hdoc->out = t[0];    
    }
}

int is_there_hdoc(t_parser *parse)
{
    t_reds *red;

    red = parse->command->red_in;
    while (red)
    {
        if(red->fd == -2)
            return (1);
        red = red->next;
    }
    return (0);
}

void hdoc(t_parser *parse)
{
    

    if(is_there_hdoc(parse))
    {
        // hdoc implementation
    }
}