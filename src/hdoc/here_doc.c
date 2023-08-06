/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:48:38 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/06 14:53:23 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void set_hdoc_pipes(t_parser *parse)
{
    int i;
    int t[2];
    t_hdoc *cur;

    cur = parse->command->heredoc;
    while (cur)
    {
        if (!cur->next)
        {
            pipe(t);
            cur->in = t[1];
            cur->out = t[0];
            break;
        }
        cur->in = -1;
        cur->out = -1;
        cur = cur->next;
    }
}

int is_last_hdoc(t_parser *parse)
{
    
}
