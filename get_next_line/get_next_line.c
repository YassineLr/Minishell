/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:15:11 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/06/17 17:22:40 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_next_line(int fd)
{
	char		*tmp;
	char		*line;
	static char	*saved;

	tmp = NULL;
	line = NULL;
	if (read(fd, NULL, 0) == -1 || BUFFER_SIZE <= 0)
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	return (fill_and_join(fd, &saved, line, tmp));
}
