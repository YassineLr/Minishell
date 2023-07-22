/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:51:20 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/22 18:16:12 by oubelhaj         ###   ########.fr       */
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

/*
	bash-3.2$	export a="a "
	bash-3.2$	ls > $a

	bash-3.2$	< $ssss
	bash:		$ssss: ambiguous redirect

	bash-3.2$	export a="a b d"
	bash-3.2$	< $a
	bash: $a:	ambiguous redirect
	bash-3.2$	< "$a"
	bash: a b d: No such file or directory
	bash-3.2$

	<< ee | <>
*/
