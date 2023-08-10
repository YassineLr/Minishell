/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 03:49:34 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 13:52:23 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	concate_val(char **key_val)
{
	t_env	*to_concate;
	char	*tmp;

	tmp = key_val[0];
	free(tmp);
	tmp = key_val[1];
	free(tmp);
	key_val[0] = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
	to_concate = search_in_env(key_val[0]);
	if (to_concate)
			to_concate->value = ft_strjoin(to_concate->value, key_val[1]);
	else
		ft_lstadd_back_env(&g_global.env, ft_lstnew_env(key_val));
	free(key_val[0]);
	free(key_val[1]);
	free(key_val);
}

void	export_no_args(void)
{
	t_env	*courant;

	courant = g_global.env;
	while (courant)
	{
		if (courant->value)
			printf("declare -x %s=\"%s\"\n", courant->key, courant->value);
		else
			printf("declare -x %s\n", courant->key);
		courant = courant->next;
	}
}

void	modify_exist_key(char **key_val)
{
	char	*tmp;

	tmp = search_in_env(key_val[0])->value;
	search_in_env(key_val[0])->value = ft_strdup(key_val[1]);
	free(tmp);
	free(key_val[0]);
	free(key_val[1]);
	free(key_val);
}

void	only_identifier(t_parser *parse, int i)
{
	char	**tmp;

	tmp = ft_split(parse->command->cmds[i], '=');
	if (!invalid_identifier(tmp[1]))
		invalid_id_err();
	else if (!search_in_env(tmp[0]))
		ft_lstadd_back_env(&g_global.env, ft_lstnew_env(tmp));
	ft_free_strs(tmp);
}

void	id_val(t_parser *parse, int i)
{
	char	**key_val;

	key_val = init_id_val(parse);
	if (!invalid_identifier(key_val[0]))
		invalid_id_err();
	else if (last_char(key_val[0]) == '+')
	{
		concate_val(key_val);
		return ;
	}
	else
	{
		if (key_exist(key_val[0]))
		{
			modify_exist_key(key_val);
			return ;
		}
		else
			ft_lstadd_back_env(&g_global.env, ft_lstnew_env(key_val));
	}
	ft_free_strs(key_val);
}
