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

int exitcode;

int	count_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int ac, char **av, char **envp)
{
	int			err;
	char		*line;
	t_lexer		*lexer;
	t_hdc		*hdc;
	t_list		*tmp_list;
	t_list		*lex_list;
	t_parser	*p_list;
	t_env		*env;
	// t_env		*courant;
	// char		**envvv;
	// int i = 0;
	// int id;
	// int status;

	(void)ac;
	(void)av;
	hdc = NULL;
	tmp_list = NULL;
	lex_list = NULL;
	line = readline("minishell-1.0$ ");
	// signals_handler(line);
	env = get_env(envp);
	while (line)
	{
		add_history(line);
		lexer = init_lexer(line);
		ft_lexer(lexer, &tmp_list, env);
		expansion(tmp_list, env);
		err = check_errors(line, tmp_list);
		if (err == 0|| err == -1)
			exitcode = 258;
		if (err != -1)
		{
			join_words(&lex_list, tmp_list);
			remove_type(&lex_list, WHITESPACE);
			hdc = here_doc(lexer, lex_list, env);
			remove_type(&lex_list, S_QUOTES);
			remove_type(&lex_list, D_QUOTES);
			if (err == 1)
			{
				p_list = ft_parser(lex_list, hdc);
				init_fds(p_list);
				set_pipes(p_list);
				executor(p_list, env, envp);
				free_plist(&p_list);
			}
		}
		free_list(&lex_list);
		free_list(&tmp_list);
		free_lexer(lexer);
		if (hdc)
			free(hdc);
		line = readline("minishell-1.0$ ");
	}
	return (0);
}
