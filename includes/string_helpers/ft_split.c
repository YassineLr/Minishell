/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 20:26:46 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/07 04:02:12 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_words(char const *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == sep)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != sep)
				i++;
		}
	}
	return (count);
}

static char	*alloc_and_fill(const char *s, int n)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * n + 1);
	if (!str)
		return (0);
	i = 0;
	while (s[i] && i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[n] = '\0';
	return (str);
}

static void	*free_(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

static char	**calcul_to_alloc(const char *s, char c, char **new_string)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
		{
			new_string[k] = alloc_and_fill(s + j, i - j);
			if (!new_string[k])
				return (free_(new_string));
			k++;
		}
	}
	new_string[k] = 0;
	return (new_string);
}

char	**ft_split(char const *s, char c)
{
	char	**new_string;

	if (!s)
		return (0);
	new_string = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!new_string)
		return (0);
	return (calcul_to_alloc(s, c, new_string));
}
