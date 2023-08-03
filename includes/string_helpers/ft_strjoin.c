/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylr <ylr@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:29:19 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/08/03 23:48:53 by ylr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	int		i;
	int		s1len;
	int		s2len;
	char	*str;

	i = -1;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = malloc(s1len + s2len + 1);
	if (!str)
		return (0);
	while (++i < s1len)
		str[i] = s1[i];
	i = -1;
	while (++i < s2len)
		str[i + s1len] = s2[i];
	str[s1len + s2len] = '\0';
	free(s1);
	// exit(10);
	return (str);
}
