/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:23:13 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/07 04:00:21 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*fill_buff(int fd)
{
	char	*buff;
	ssize_t	rd_bytes;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	rd_bytes = read(fd, buff, BUFFER_SIZE);
	if (rd_bytes > 0)
	{
		buff[rd_bytes] = '\0';
		return (buff);
	}
	free(buff);
	return (NULL);
}

char	*fill_and_join(int fd, char **saved, char *line, char *tmp)
{
	while (!ft_strchr(*saved, '\n'))
	{
		tmp = fill_buff(fd);
		if (!tmp)
		{
			line = *saved;
			*saved = NULL;
			return (line);
		}
		*saved = ft_strjoin(*saved, tmp);
		free(tmp);
	}
	line = ft_substr(*saved, 0, ft_strchr(*saved, '\n') - *saved + 1);
	tmp = *saved;
	*saved = ft_substr(ft_strchr(*saved, '\n') + 1, 0,
			ft_strlen(ft_strchr(*saved, '\n')));
	free(tmp);
	return (line);
}
