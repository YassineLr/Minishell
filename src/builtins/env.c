/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:23:15 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 02:42:22 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(void)
{
	t_env	*cur;

	if (g_global.env)
	{
		cur = g_global.env;
		while (cur)
		{
			if (cur->key && cur->value)
			{
				if (!cur->value)
					printf("%s=\n", cur->key);
				else
					printf("%s=%s\n", cur->key, cur->value);
			}
			cur = cur->next;
		}
	}
	g_global.exitcode = 0;
}
