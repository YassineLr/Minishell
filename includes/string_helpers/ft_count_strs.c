/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_strs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 04:40:14 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/26 04:40:15 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_strs(char **str)
{
	int	i;
	
	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
