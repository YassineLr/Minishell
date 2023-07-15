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

#include "../minishell.h"

int	count_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	remove_spaces(t_list **head)
{
	t_list *current;
	t_list *prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if ((current->token->type == WHITESPACE && current->next->token->type != WORD)
			|| (current->token->type == WHITESPACE && prev->token->type != WORD))
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
	// char		*pwd=NULL;
	t_lexer		*lexer;
	t_list		*lex_list;
	// t_parser	*p_list;
	// t_env		*env;
	// t_env		*courant;
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
			// remove_spaces(&lex_list);
			while (lex_list)
			{
				printf("Value :  %s\nType  :  %d\n\n", lex_list->token->value, lex_list->token->type);
				lex_list = lex_list->next;
			}
			// p_list = ft_parser(lex_list, hdoc_input);
		}
		// int i = -1;
		// while (p_list->command->cmds[++i])
		// 	printf("%s\n", p_list->command->cmds[i]);
		// int jk = 0;
		// env = execc_get_env(envp);
		// export(p_list, env);
		// courant = env;
		// while (courant)
		// {
		// 	printf("%s  =  %s\n", courant->key,courant->value);
		// 	courant = courant->next;
		// }
		// printf("\n");
		add_history(line);
		free_lexer(lexer);
		free_list(&lex_list);
		line = readline("minishell-1.0$ ");
	}
		// int i;
		// while (p_list)
		// {
		// 	printf("%d\n", p_list->command->append);
		// 	// printf("%d\n", *(p_list->command->heredoc));
		// 	printf("%d\n", p_list->command->pipe);
		// 	printf("%d\n", p_list->command->red_in);
		// 	printf("%d\n", p_list->command->red_out);
		// 	p_list = p_list->next;
		// }
}