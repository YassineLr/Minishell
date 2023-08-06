/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 12:48:38 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/06 18:38:57 by oubelhaj         ###   ########.fr       */
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

void    here_doc(t_parser *parser, t_env *env)
{
	int		expand;
	char	*hdoc_line;

	expand = 1;
	while (parser->command->red_in)
	{
        if (parser->command->red_in->fd == -2)
        {
            hdoc_line = readline("> ");
            while (ft_strcmp(hdoc_line, parser->command->red_in->hdoc->delim))
		    {
                if (!parser->command->red_in->next)
                {
		    	    // if (expand == 0)
		    	    	ft_putendl_fd(hdoc_line, parser->command->red_in->hdoc->in);
		    	    // else
		    	    // 	heredoc_expand(hdoc_line, env, parser->command->red_in->hdoc->in);
                }
		    	if (hdoc_line)
		    		free(hdoc_line);
		    	hdoc_line = readline("> ");
            }
        }
        parser->command->red_in = parser->command->red_in->next;
    }
    exit(1);
}

void hdoc(t_parser *parse, t_env *env)
{
    

    if(is_there_hdoc(parse))
    {
        here_doc(parse, env);
    }
}