/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opening.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 10:59:22 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/31 11:30:18 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_filename(char *name)
{
	int		i;
	char	**str;

	i = 0;
	if (name[0] == '\0')
		return (1);
	str = ft_split(name, ' ');
	if (ft_count_strs(str) != 1)
		return (1);
	ft_free_strs(str);
	return (0);
}

int	file_error(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	return (-1);
}

int	open_redin(t_list *list)
{
	int	fd;

	if (list->token->expanded == 1 && list->token->in_quotes == 0)
	{
		if (check_filename(list->token->value))
		{
			write(2, "minishell: ambiguous redirect\n", 31);
			return (-1);
		}
		else
		{
			fd = open(list->token->value, O_RDONLY);
			if (fd == -1)
				return (file_error(list->token->value));
		}
	}
	else
	{
		fd = open(list->token->value, O_RDONLY);
		if (fd == -1)
			return (file_error(list->token->value));
	}
	return (fd);
}

int	open_redout(t_list *list)
{
	int	fd;

	if (list->token->expanded == 1 && list->token->in_quotes == 0)
	{
		if (check_filename(list->token->value))
		{
			write(2, "minishell: ambiguous redirect\n", 31);
			return (-1);
		}
		else
		{
			fd = open(list->token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (file_error(list->token->value));
		}
	}
	else
	{
		fd = open(list->token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (file_error(list->token->value));
	}
	return (fd);
}

int	open_append(t_list *list)
{
	int	fd;

	if (list->token->expanded == 1 && list->token->in_quotes == 0)
	{
		if (check_filename(list->token->value))
		{
			write(2, "minishell: ambiguous redirect\n", 31);
			return (-1);
		}
		else
		{
			fd = open(list->token->value, O_APPEND | O_WRONLY | O_CREAT, 0644);
			if (fd == -1)
				return (file_error(list->token->value));
		}
	}
	else
	{
		fd = open(list->token->value, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			return (file_error(list->token->value));
	}
	return (fd);
}
