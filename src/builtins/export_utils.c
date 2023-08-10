/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:53:22 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 13:44:47 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	invalid_id_err(void)
{
	ft_putstr_fd("invalid identifier\n", 2);
	g_global.exitcode = 1;
}

int	key_exist(char *key)
{
	if (search_in_env(key))
		return (1);
	return (0);
}

int	invalid_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] && i < ft_strlen(str) - 1)
	{
		if (!(str[i] == '_' || ft_isalnum(str[i])))
			return (0);
		i++;
	}
	if (!(str[i] == '_' || ft_isalnum(str[i]) || str[i] == '+'))
		return (0);
	return (1);
}

char	last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
		i++;
	return (str[i]);
}

char	**init_id_val(t_parser *parse)
{
	char	**key_val;

	key_val = ft_calloc(2, sizeof(char *));
	key_val[0] = ft_substr(parse->command->cmds[i], 0,
			index_at(parse->command->cmds[i], '='));
	if (last_char(parse->command->cmds[i]) == '=')
		key_val[1] = ft_strdup("");
	else if (ft_strchr(parse->command->cmds[i], '='))
		key_val[1] = ft_strdup(ft_strchr(parse->command->cmds[i], '=') + 1);
	return (key_val);
}
