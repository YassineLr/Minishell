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

int	main(int ac, char **av, char **envp)
{
	int		*hdoc_pipe;
	char	*line;
	t_lexer	*lexer;
	t_list	*lexer_list;
	// t_list	*node;

	(void)ac;
	(void)av;
	lexer_list = NULL;
	line = readline("minishell-1.0$ ");
	while (line)
	{
		check_errors(line);
		hdoc_pipe = here_doc(line);
		if (hdoc_pipe == NULL)
			return (0);
		lexer = init_lexer(line, envp);
		if (lexer)
		{
			ft_lexer(lexer, &lexer_list);
			// ft_parser(lexer_list, hdoc_pipe);
		}
		// while (lexer_list)
		// {
		// 	printf("WORD :  %s\nType :  %d\n", lexer_list->token->value, lexer_list->token->type);
		// 	lexer_list = lexer_list->next;
		// }
		// printf("\n");
		free_lexer(lexer);
		free(lexer_list);
		lexer_list = NULL;
		add_history(line);
		free(line);
		line = readline("minishell-1.0$ ");
	}
}
