/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:20:23 by ylarhris          #+#    #+#             */
/*   Updated: 2023/08/10 19:42:16 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*t__t;

	t__t = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		t__t[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
