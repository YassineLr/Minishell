/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:06:58 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/05 15:50:36 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expansion_v2(char *str, t_env *env, int fd)
{
	char	*final_str;
	
	final_str = expand_(str, env);
	if (final_str)
	{
		ft_putendl_fd(final_str, fd);
		free(final_str);
	}
}
