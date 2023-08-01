/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:58:16 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/01 10:36:09 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redir(int type)
{
	if (is_redir_2(type) || type == HEREDOC)
		return (1);
	return (0);
}

int	is_redir_2(int type)
{
	if (type == RED_IN || type == RED_OUT || type == APPEND)
		return (1);
	return (0);
}
