/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:51:20 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/28 03:10:06 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expansion(t_lexer *lexer, t_env *env)
{
	int		start;
	int		len;
	char	*str;

	len = 0;
	lexer_advance(lexer);
	start = lexer->i;
	while (lexer->c && !is_special(lexer->c))
	{
		len++;
		lexer_advance(lexer);
	}
	str = ft_substr(lexer->content, start, len);
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			break;
		env = env->next;
	}
	if (env)
	{
		free(str);
		return (ft_strdup(env->value));
	}
	free(str);
	return (ft_strdup(""));
}
