/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:51:20 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/02 17:13:57 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expansion(t_lexer *lexer)
{
	int		i;
	int		start;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	lexer_advance(lexer);
	start = lexer->i;
	while (lexer->c && !is_special(lexer->c))
	{
		len++;
		lexer_advance(lexer);
	}
	str = ft_substr(lexer->content, start, len);
	while (lexer->env[i] && ft_strcmp(str, lexer->env[i]->key) != 0)
		i++;
	if (lexer->env[i])
	{
		free(str);
		return (lexer->env[i]->value);
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
