/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:40:04 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/05/26 18:40:04 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_env	**get_env(char **ev)
{
	int		i;
	char	**str;
	t_env	**env;

	i = 0;
	env = malloc(sizeof(t_env *) * (count_env(ev) + 1));
	while (ev[i])
	{
		env[i] = malloc(sizeof(t_env));
		str = ft_split(ev[i], '=');
		env[i]->key = ft_strdup(str[0]);
		env[i]->value = ft_strdup(str[1]);
		ft_free_strs(str);
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	remove_quotes(t_list **head)
{
	t_list *current;
	t_list *prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (current->token->type == QUOTES)
		{
			if (prev == NULL)
			{
				*head = current->next;
				ft_lstdelone(current, &free);
				current = *head;
			}
			else
			{
				prev->next = current->next;
				ft_lstdelone(current, &free);
				current = prev->next;
			}
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	int			err;
	int			*hdoc_input;
	char		*line;
	t_lexer		*lexer;
	t_list		*lex_list;
	t_parser	*p_list;
	// t_list	*node;

	(void)ac;
	(void)av;
	lex_list = NULL;
	line = readline("minishell-1.0$ ");
	while (line)
	{
		lexer = init_lexer(line, envp);
		ft_lexer(lexer, &lex_list);
		err = check_errors(line, lex_list);
		if (err != -1)
		{
			hdoc_input = here_doc(lexer, lex_list);
			remove_quotes(&lex_list);
			p_list = ft_parser(lex_list, hdoc_input);
		}
		while (lex_list)
		{
			printf("Value :  %s\nType  :  %d\n\n", lex_list->token->value, lex_list->token->type);
			lex_list = lex_list->next;
		}
		printf("\n");
		free_lexer(lexer);
		free(lex_list);
		lex_list = NULL;
		add_history(line);
		free(line);
		line = readline("minishell-1.0$ ");
	}
}


		// int i;
		// while (p_list)
		// {
		// 	i = -1;
		// 	while (p_list->command->cmds[++i])
		// 		printf("%s\n", p_list->command->cmds[i]);
		// 	printf("%d\n", p_list->command->append);
		// 	// printf("%d\n", *(p_list->command->heredoc));
		// 	printf("%d\n", p_list->command->pipe);
		// 	printf("%d\n", p_list->command->red_in);
		// 	printf("%d\n", p_list->command->red_out);
		// 	p_list = p_list->next;
		// }