/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 03:49:34 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/04 06:19:21 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int key_exist(t_env *env, char **key_val)
{
	if(search_in_env(env,key_val[0]))
		return(1);
	return (0);
}

int invalid_identifier(char *str)
{
	int i;

	i = 0;
	while (str[i] && i < ft_strlen(str) - 1)
	{
		if(!(str[i] == '_' || ft_isalnum(str[i])))
			return(0);
		i++;
	}
	if(!(str[i] == '_' || ft_isalnum(str[i]) || str[i] == '+'))
			return(0);
	return(1);
}
void concate_val(t_env *env, char **key_val)
{
	t_env   *to_concate;
	
	key_val[0] = ft_substr(key_val[0],0,ft_strlen(key_val[0])-1);
	to_concate = search_in_env(env,key_val[0]);
	if(to_concate)
			to_concate->value = ft_strjoin(to_concate->value, key_val[1]);
	else
		ft_lstadd_back_env(&env,ft_lstnew_env(key_val));
	// free(key_val[0]);
}

char last_char(char *str)
{
	int i;

	i = 0;
	while(str[i+1])
		i++;
	return str[i];
}

void    export_no_args(t_env *env)
{
	t_env   *courant;

	courant = env;
	while (courant)
	{
		if(courant->value)
			printf("declare -x %s=\"%s\"\n", courant->key, courant->value);
		else
			printf("declare -x %s\n", courant->key);
		courant = courant->next;
	}
}

void	export(t_parser *parse, t_env **env)
{
	char	**key_val;
	char	*tmp;
	char	*tmpp;
	int		i = 1;

	if (!parse->command->cmds[1])
	{
		export_no_args(*env);
		return ;
	}
	while (parse->command->cmds[i])
	{
		if (!(parse->command->cmds[i][0] == '_' || ft_isalnum(parse->command->cmds[i][0])))
			ft_putstr_fd("invalid identifier\n", 2);
		else if (index_at(parse->command->cmds[i],'=') != -1)
		{
			key_val = malloc(2*sizeof(char*));
			key_val[0] = ft_substr(parse->command->cmds[i], 0, index_at(parse->command->cmds[i],'='));
			key_val[1] = ft_strdup(ft_strchr(parse->command->cmds[i],'=')+1);
			tmp = key_val[0];
			tmpp = key_val[1];
			if(!invalid_identifier(key_val[0]))
				ft_putstr_fd("invalid identifier 2\n",2);
			else if(last_char(key_val[0]) == '+')
				concate_val(*env, key_val);
			else
			{
				if (key_exist(*env, key_val))
					search_in_env(*env, key_val[0])->value = key_val[1];
				else
					ft_lstadd_back_env(env,ft_lstnew_env(key_val));
			}
			// free(tmp);
			// free(tmpp);
		}
		else if (index_at(parse->command->cmds[i],'=') == -1)
		{
			char **tmp = ft_split(parse->command->cmds[i], '=');
			if(search_in_env(*env, tmp[0]))
				search_in_env(*env, tmp[0])->value = "";
			else
				ft_lstadd_back_env(env,ft_lstnew_env(tmp));
			ft_free_strs(tmp);
		}
		i++;
	}
}
