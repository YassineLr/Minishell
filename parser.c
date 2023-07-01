/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:08:00 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/07/01 11:54:36 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->token->type != WORD && list->token->type != WHITESPACE)
			break;
		list = list->next;
		count++;
	}
	return (count);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->pipe = 0;
	cmd->red_in = 0;
	cmd->red_out = 0;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->cmds = 0;
	return (cmd);
}

t_parser	*ft_parser(t_list *list, int *hdc_pipe)
{
	int			i;
	// int		hdc;
	int			count;
	t_cmd		*cmd;
	t_parser	*p_list;

	p_list = NULL;
	(void)hdc_pipe;
	while (list)
	{
		i = 0;
		cmd = init_cmd();
		if (!cmd)
			return (0);
		count = count_words(list);
		cmd->cmds = malloc(sizeof(char *) * (count + 1));
		while (list && (list->token->type == WORD || list->token->type == WHITESPACE))
		{
			cmd->cmds[i] = ft_strdup(list->token->value);
			list = list->next;
			i++;
		}
		cmd->cmds[i] = NULL;
		if (list)
		{
			if (list->token->type == WHITESPACE)
				list = list->next;
			if (list->token->type == PIPE)
			{
				cmd->pipe = 1;
				if (list->next->token->type == WHITESPACE)
					list = list->next;
			}
			else if (list->token->type == RED_IN)
			{
				list = list->next;
				if (list->token->type == WHITESPACE)
					list = list->next;
				cmd->red_in = open_redin(list->token->value);
			}
			else if (list->token->type == RED_OUT)
			{
				list = list->next;
				if (list->token->type == WHITESPACE)
					list = list->next;
				cmd->red_out = open_redout(list->token->value);
			}
			else if (list->token->type == APPEND)
			{
				list = list->next;
				if (list->token->type == WHITESPACE)
					list = list->next;
				cmd->red_in = open_append(list->token->value);
			}
			list = list->next;
		}
		ft_lstadd_back_alt(&p_list, ft_lstnew_alt(cmd));
		// if (cmd->cmds)
		// 	ft_free_strs(cmd->cmds);
		// if (cmd)
		// {
		// 	free(cmd);
		// 	cmd = NULL;
		// }
	}
	// while (p_list)
	// {
	// 	i = -1;
	// 	printf("-----------------------\n");
	// 	while (p_list->command->cmds[++i])
	// 		printf("%s\n", p_list->command->cmds[i]);
	// 	printf("%d\n", p_list->command->append);
	// 	printf("%d\n", p_list->command->heredoc);
	// 	printf("%d\n", p_list->command->pipe);
	// 	printf("%d\n", p_list->command->red_in);
	// 	printf("%d\n", p_list->command->red_out);
	// 	p_list = p_list->next;
	// }
	return (p_list);
}
