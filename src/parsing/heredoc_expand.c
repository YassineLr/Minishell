/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:06:58 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/03 03:07:18 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expansion_v2(t_lexer *lexer, char *str, int fd, t_env *env)
{
	int		i;
	int		j;
	char	*tmp;
	int		start;
	int		len;
	int		s_len;
	char	*final_str;

	i = 0;
	j = 0;
	s_len = ft_strlen(str);
	final_str = malloc(sizeof(char));
	if (!final_str)
		return ;
	final_str[0] = '\0';
	while (str[i])
	{
		j = 0;
		len = 0;
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '$')
			{
				final_str = ft_strjoin(final_str, "$$");
				i++;
			}
			else
			{
				start = i;
				while (str[i] && str[i] != '$' && !ft_is_whitespace(str[i]))
				{
					i++;
					len++;
				}
				tmp = ft_substr(str, start, len);
				while (env)
				{
					if (ft_strcmp(tmp, env->key) == 0)
						break;
					env = env->next;
				}
				if (env)
					final_str = ft_strjoin(final_str, env->value);
				if (tmp)
				{
					free(tmp);
					tmp = NULL;
				}
			}
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
			{
				i++;
				len++;
			}
			tmp = ft_substr(str, start, len);
			final_str = ft_strjoin(final_str, tmp);
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
		}
	}
	if (final_str)
	{
		ft_putendl_fd(final_str, fd);
		free(final_str);
	}
}
