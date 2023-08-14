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

t_meta_data	g_global;

void	free_lex(t_list **tmp_list, t_lexer *lexer)
{
	free_list(tmp_list);
	free_lexer(lexer);
}

void	parse_and_exec(t_list *lex_list, t_hdc *hdc)
{
	t_parser	*plist;

	plist = ft_parser(lex_list, hdc);
	if (plist)
	{
		init_fds(plist);
		set_pipes(plist);
		executor(plist);
		free_plist(&plist);
	}
}

void	minishell(t_list *tmp_list, int err)
{
	t_hdc		*hdc;
	t_list		*lex_list;

	lex_list = NULL;
	expansion(tmp_list);
	join_words(&lex_list, tmp_list);
	remove_type(&lex_list, WHITESPACE);
	hdc = here_doc(lex_list, &err);
	remove_nulls(&lex_list);
	remove_type(&lex_list, S_QUOTES);
	remove_type(&lex_list, D_QUOTES);
	if (err == 1)
		parse_and_exec(lex_list, hdc);
	free_list(&lex_list);
	free_hdc(hdc);
}

int	main(int ac, char **av, char **envp)
{
	int			err;
	char		*line;
	t_lexer		*lexer;
	t_list		*tmp_list;

	(void)ac;
	(void)av;
	tmp_list = NULL;
	g_global.env = get_env(envp);
	while (1)
	{
		signals_handler();
		line = readline("minishell-1.0$ ");
		if (!line)
			ctrl_d();
		signal(SIGINT, SIG_IGN);
		add_history(line);
		lexer = init_lexer(line);
		ft_lexer(lexer, &tmp_list);
		err = check_errors(line, tmp_list);
		if (err != -1)
			minishell(tmp_list, err);
		free_lex(&tmp_list, lexer);
	}
	return (0);
}
