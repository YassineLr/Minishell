/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_not_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:47:57 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/06/16 12:52:58 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_special(char c)
{
	if (c == '\'' || c == '"' || ft_is_whitespace(c)
		|| c == '>' || c == '<' || c == '|')
		return (0);
	return (1);
}
