/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:00:41 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/06/14 11:43:15 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strstr(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (!haystack || !needle)
		return (2);
	while (haystack[i])
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && (haystack[i + j] && needle[j]))
			j++;
		if (needle[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}
