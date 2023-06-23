/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:24:41 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/06/17 17:25:08 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(char *buff, char c)
{
	if (buff != NULL)
	{
		while (*buff && *buff != c)
			buff++;
		if (*buff == c)
			return (buff);
	}
	return (NULL);
}
