/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:33:44 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/10 19:42:38 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, int len)
{
	int	i;
	int	j;
	int	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (!haystack && !len)
		return (0);
	if (needle_len == 0)
		return ((char *)haystack);
	while (haystack[i] && len >= needle_len)
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && (haystack[i + j] && needle[j]))
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
		len--;
	}
	return (0);
}
