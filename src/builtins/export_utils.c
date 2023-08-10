/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:53:22 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 02:42:34 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	invalid_id_err(void)
{
	ft_putstr_fd("invalid identifier\n", 2);
	g_global.exitcode = 1;
}

int	key_exist(char **key_val)
{
	if (search_in_env(key_val[0]))
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
