/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 03:49:34 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/09 19:04:52 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int key_exist(char **key_val)
{
	if(search_in_env(key_val[0]))
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

void concate_val(char **key_val)
{
	t_env   *to_concate;
	
	key_val[0] = ft_substr(key_val[0],0,ft_strlen(key_val[0])-1);
	to_concate = search_in_env(key_val[0]);
	if(to_concate)
			to_concate->value = ft_strjoin(to_concate->value, key_val[1]);
	else
		ft_lstadd_back_env(&global.env,ft_lstnew_env(key_val));
}

char last_char(char *str)
{
	int i;

	i = 0;
	while(str[i+1])
		i++;
	return str[i];
}

void    export_no_args()
{
	t_env   *courant;

	courant = global.env;
	while (courant)
	{
		if(courant->value)
			printf("declare -x %s=\"%s\"\n", courant->key, courant->value);
		else
			printf("declare -x %s\n", courant->key);
		courant = courant->next;
	}
}

void	only_identifier(t_parser *parse,int i)
{
	char **tmp;

	tmp = ft_split(parse->command->cmds[i], '=');
	if(!search_in_env(tmp[0]))
		ft_lstadd_back_env(&global.env,ft_lstnew_env(tmp));
	ft_free_strs(tmp);
}

void invalid_id_err(void)
{
	ft_putstr_fd("invalid identifier\n", 2);
    global.exitcode = 1;
}
void	id_val(t_parser *parse, int i)
{
	char **key_val;
	
	key_val = ft_calloc(2,sizeof(char*));
	key_val[0] = ft_substr(parse->command->cmds[i], 0, index_at(parse->command->cmds[i],'='));
	if(last_char(parse->command->cmds[i]) == '=')
		key_val[1] = ft_strdup("");
	else if(ft_strchr(parse->command->cmds[i],'='))
		key_val[1] = ft_strdup(ft_strchr(parse->command->cmds[i],'=')+1);	
	if(!invalid_identifier(key_val[0]))
		invalid_id_err();
	else if(last_char(key_val[0]) == '+')
	{
		free(key_val[0]);
		concate_val(key_val);
	}
	else
	{
		if (key_exist(key_val))
			search_in_env(key_val[0])->value = ft_strdup(key_val[1]);
		else
			ft_lstadd_back_env(&global.env,ft_lstnew_env(key_val));
	}
	free(key_val[0]);
	free(key_val[1]);
	free(key_val);
}

void	export(t_parser *parse)
{
	int		i = 1;

    global.exitcode = 0;
	if (!parse->command->cmds[1])
	{
		export_no_args();
		return ;
	}
	while (parse->command->cmds[i])
	{
		if (parse->command->cmds[i][0] != '_' && !ft_isalpha(parse->command->cmds[i][0]))
			invalid_id_err();
		else if (index_at(parse->command->cmds[i],'=') != -1)
			id_val(parse, i);
		else if (index_at(parse->command->cmds[i],'=') == -1)
			only_identifier(parse, i);
		i++;
	}
}
