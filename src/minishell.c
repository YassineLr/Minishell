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

void	remove_type(t_list **head, int type)
{
	t_list *current;
	t_list *prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if ((int)current->token->type == type)
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

t_list **join_words(t_list **list, t_list *tmp_list)
{
	int		flag;
	char	*tmp;
	int		expand;
	t_token	*token;
	int		in_quotes;

	flag = 0;
	in_quotes = 0;
	expand = 0;
	token = NULL;
	// tmp = NULL;
	while (tmp_list)
	{
		if (tmp_list->token->type != WORD && tmp_list->token->type != S_QUOTES && tmp_list->token->type != D_QUOTES)
		{

			ft_lstadd_back(list, ft_lstnew(init_token(tmp_list->token->type, ft_strdup(tmp_list->token->value))));
			tmp_list = tmp_list->next;
		}
		else
		{
			tmp = malloc(sizeof(char));
			tmp[0] = '\0';
			while (tmp_list && tmp_list->token)
			{
				if (tmp_list->token->type == WORD)
				{
					tmp = ft_strjoin(tmp, tmp_list->token->value);
					if (tmp_list->token->expanded)
						expand = 1;
					if (tmp_list->token->in_quotes)
						in_quotes = 1;
					tmp_list = tmp_list->next;
				}
				else if (tmp_list->token->type == S_QUOTES || tmp_list->token->type == D_QUOTES)
				{
					flag = 1;
					tmp_list = tmp_list->next;
				}
				else
					break;
			}
			if (flag == 1)
				ft_lstadd_back(list, ft_lstnew(init_token(S_QUOTES, lexer_char_to_string('\''))));
			token = init_token(WORD, ft_strdup(tmp));
			if (expand == 1)
				token->expanded = 1;
			if (in_quotes == 1)
				token->in_quotes = 1;
			ft_lstadd_back(list, ft_lstnew(token));
			free(tmp);
		}
		if (!tmp_list)
			break;
	}
	// ft_lstclear(&tmp_list, &free);
	return (list);
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
	env = execc_get_env(envp);
	while (line)
	{
		add_history(line);
		lexer = init_lexer(line);
		ft_lexer(lexer, &tmp_list, env);
		expansion(tmp_list, env);
		err = check_errors(line, tmp_list);
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
				int x;
				t_parser *p;
				p = p_list;
				while (p)
				{
					x = -1;
					while (p->command->cmds[++x])
						printf("cmds[%d]  : %s\n", x, p->command->cmds[x]);
					printf("pipe     : %d\n", p->command->pipe);
					printf("red_in   : %d\n", p->command->red_in);
					printf("red_out  : %d\n", p->command->red_out);
					p = p->next;
					printf("\n");
				}
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
