/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:45:31 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 18:08:14 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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