/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 11:32:23 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/19 08:43:35 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_substr(char const *s, int start, int len)
{
	int		i;
	int		rem;
	int		s_len;
	char	*substr;

	i = 0;
	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		rem = 0;
	else if (s_len - start < len)
		rem = s_len - start;
	else
		rem = len;
	substr = malloc(sizeof(char) * rem + 1);
	if (!substr)
		return (0);
	while (i < rem)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
