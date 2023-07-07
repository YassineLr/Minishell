/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:29:12 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/06/02 20:29:12 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_strs(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return;
	while (str[i])
		free(str[i++]);
	free(str);
}
