/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 03:49:34 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 21:09:44 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	concate_val(char **key_val)
{
	t_env	*to_concate;

	key_val[0] = ft_substr(key_val[0], 0, ft_strlen(key_val[0]) - 1);
	to_concate = search_in_env(key_val[0]);
	if (to_concate)
			to_concate->value = ft_strjoin(to_concate->value, key_val[1]);
	else
		ft_lstadd_back_env(&g_global.env, ft_lstnew_env(key_val));
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
	if (!invalid_identifier(tmp[0]))
		invalid_id_err();
	else if (!search_in_env(tmp[0]))
		ft_lstadd_back_env(&g_global.env, ft_lstnew_env(tmp));
	ft_free_strs(tmp);
}

void	id_val(t_parser *parse, int i)
{
	char	**key_val;

	key_val = ft_calloc(2, sizeof(char *));
	key_val[0] = ft_substr(parse->command->cmds[i], 0,
			index_at(parse->command->cmds[i], '='));
	if (last_char(parse->command->cmds[i]) == '=')
		key_val[1] = ft_strdup("");
	else if (ft_strchr(parse->command->cmds[i], '='))
		key_val[1] = ft_strdup(ft_strchr(parse->command->cmds[i], '=') + 1);
	if (!invalid_identifier(key_val[0]))
		invalid_id_err();
	else if (last_char(key_val[0]) == '+')
	{
		free(key_val[0]);
		concate_val(key_val);
	}
	else
		new_id_val(key_val);
	free(key_val[0]);
	free(key_val[1]);
	free(key_val);
}
