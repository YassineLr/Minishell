/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:45:31 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/11 01:35:56 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	new_id_val(char **key_val)
{
	char	*to_free;

	if (key_exist(key_val[0]))
	{
		to_free = search_in_env(key_val[0])->value;
		search_in_env(key_val[0])->value = ft_strdup(key_val[1]);
		free(to_free);
	}
	else
		ft_lstadd_back_env(&g_global.env, ft_lstnew_env(key_val));
}

void	export(t_parser *parse)
{
	int	i;

	i = 1;
	g_global.exitcode = 0;
	if (!parse->command->cmds[1])
	{
		export_no_args();
		return ;
	}
	while (parse->command->cmds[i])
	{
		if (parse->command->cmds[i][0] != '_' &&
			!ft_isalpha(parse->command->cmds[i][0]))
			invalid_id_err();
		else if (index_at(parse->command->cmds[i], '=') != -1)
			id_val(parse, i);
		else if (index_at(parse->command->cmds[i], '=') == -1)
			only_identifier(parse, i);
		i++;
	}
}
