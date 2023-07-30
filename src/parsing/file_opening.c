/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opening.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylarhris <ylarhris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 10:59:22 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/30 03:22:48 by ylarhris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_filename(char *name)
{
	// still testing
	int	i;
	
	i = 0;
	while (ft_is_whitespace(name[i]))
		i++;
	if (name[i] != '\0')
		return (1);
	return (0);
}

int	open_redin(char *filename)
{
	int	fd;

	if (!check_filename(filename))
	{
	 	write(2, "minishell: ambiguous redirect\n", 31);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("");
		return (-1);
	}
	return (fd);
}

int	open_redout(char *filename)
{
	int	fd;

	if (!check_filename(filename))
	{
	 	write(2, "minishell: ambiguous redirect\n", 31);
		return (-1);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("");
		return (-1);
	}
	return (fd);
}

int	open_append(char *filename)
{
	int	fd;

	fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("");
		return (-1);
	}
	return (fd);
}
