/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:04:21 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/11 01:37:10 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_env(void)
{
	int		count;
	t_env	*env;

	count = 0;
	if (g_global.env)
	{
		env = g_global.env;
		while (env)
		{
			count++;
			env = env->next;
		}
	}
	return (count);
}

void	free_env(t_env *courant)
{
	free(courant->key);
	free(courant->value);
	free(courant);
}

int	remove_first(char *key)
{
	t_env	*tmp;

	if (!ft_strcmp(g_global.env->key, key))
	{
		if (count_env() == 1)
		{
			ft_lstclear_env(&g_global.env, free);
			g_global.env = NULL;
		}
		else
		{
			tmp = g_global.env;
			if (g_global.env->next)
				g_global.env = g_global.env->next;
			free(tmp->key);
			free(tmp->value);
		}
		return (1);
	}
	return (0);
}

void	remove_variable(char *key)
{
	t_env	*precourant;
	t_env	*courant;

	if (!g_global.env)
		return ;
	if (remove_first(key))
		return ;
	else
	{
		courant = (g_global.env)->next;
		precourant = g_global.env;
		while (courant)
		{
			if (!ft_strcmp(courant->key, key))
			{
				precourant->next = courant->next;
				ft_lstdelone_env(courant, free);
				return ;
			}
			precourant = precourant->next;
			courant = courant->next;
		}
	}
}

void	unset(t_parser *parse)
{
	int	i;

	g_global.exitcode = 0;
	i = 1;
	while (parse->command->cmds[i])
	{
		if (!invalid_identifier(parse->command->cmds[i]))
			invalid_id_err();
		else if (search_in_env(parse->command->cmds[i]))
			remove_variable(parse->command->cmds[i]);
		i++;
	}
}
