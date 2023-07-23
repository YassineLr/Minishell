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

	flag = 0;
	// tmp = NULL;
	while (tmp_list)
	{
		if (tmp_list->token->type != WORD && tmp_list->token->type != QUOTES)
			ft_lstadd_back(list, ft_lstnew(init_token(tmp_list->token->type, ft_strdup(tmp_list->token->value))));
		else
		{
			tmp = malloc(sizeof(char));
			tmp[0] = '\0';
			while (tmp_list && tmp_list->token)
			{
				if (tmp_list->token->type == WORD)
				{
					tmp = ft_strjoin(tmp, tmp_list->token->value);
					tmp_list = tmp_list->next;
				}
				else if (tmp_list->token->type == QUOTES)
				{
					flag = 1;
					tmp_list = tmp_list->next;
				}
				else
					break;
			}
			if (flag == 1)
				ft_lstadd_back(list, ft_lstnew(init_token(QUOTES, lexer_char_to_string('\''))));
			ft_lstadd_back(list, ft_lstnew(init_token(WORD, ft_strdup(tmp))));
			free(tmp);
		}
		if (!tmp_list)
			break;
		tmp_list = tmp_list->next;
	}
	// ft_lstclear(&tmp_list, &free);
	return (list);
}


int	main(int ac, char **av, char **envp)
{
	int			err;
	int			*hdoc_input;
	char		*line;
	// char		*pwd=NULL;
	t_lexer		*lexer;
	t_list		*tmp_list;
	t_list		*lex_list;
	t_parser	*p_list;
	t_parser	*current;
	t_env		*env;
	t_env		*courant;
	char		**envvv;
	int i = 0;
	int status;
	// t_list	*node;

	(void)ac;
	(void)av;
	tmp_list = NULL;
	lex_list = NULL;
	line = readline("minishell-1.0$ ");
	env = execc_get_env(envp);
	while (line)
	{
		lexer = init_lexer(line);
		ft_lexer(lexer, &tmp_list, env);
		err = check_errors(line, tmp_list);
		if (err != -1)
		{
			join_words(&lex_list, tmp_list);
			remove_type(&lex_list, WHITESPACE);
			hdoc_input = here_doc(lexer, lex_list, env);
			remove_type(&lex_list, QUOTES);
			if (err != 0)
				p_list = ft_parser(lex_list, hdoc_input);
			// int i;
			// while (p_list)
			// {
			// 	i = -1;
			// 	while (p_list->command->cmds[++i])
			// 		printf("cmd[%d] : %s\n", i, p_list->command->cmds[i]);
			// 	printf("pipe : %d\n", p_list->command->pipe);
			// 	printf("red_in : %d\n", p_list->command->red_in);
			// 	printf("red_out : %d\n", p_list->command->red_out);
			// 	p_list = p_list->next;
			// }
		}
		printf("here 1\n");
		init_fds(p_list);
		// current = p_list;
		// printf("======== after init\n");
		// while (current)
		// {
		// 	printf("read : %d\n", current->command->pipe_fd.read);
		// 	printf("to_close : %d\n", current->command->pipe_fd.to_close);
		// 	printf("write : %d\n", current->command->pipe_fd.write);
		// 	current = current->next;
		// }
		printf("here 2\n");
		set_pipes(p_list);
		// printf("======== setting pipes\n");

		// current = p_list;
		// while (current)
		// {
		// 	printf("read : %d\n", current->command->pipe_fd.read);
		// 	printf("to_close : %d\n", current->command->pipe_fd.to_close);
		// 	printf("write : %d\n", current->command->pipe_fd.write);
		// 	current = current->next;
		// }
		printf("here 3\n");

		while (p_list)
		{
			execute_cmd(p_list, env , envp);
			printf("haha\n");
			p_list = p_list->next;
		}
		
		// printf("here\n");
		while (waitpid(-1, &status, 0) != -1);
		
		// envvv = env_in_tab(env);
		// while (envvv[i])
		// {
		// 	printf("%s\n",envvv[i]);
		// 	i++;
		// }
		
		// int i = -1;
		// while (p_list->command->cmds[++i])
		// 	printf("%s\n", p_list->command->cmds[i]);
		// int jk = 0;
		// printf("===== before =====\n");
		// courant = env;
		// while (courant)
		// {
		// 	printf("%s  =  %s\n", courant->key,courant->value);
		// 	courant = courant->next;
		// }
		/*if(!strcmp(p_list->command->cmds[0],"export"))
			export(p_list,&env);
		if(!strcmp(p_list->command->cmds[0],"unset"))
			unset(p_list,env);
		if(!strcmp(p_list->command->cmds[0],"cd"))
			cd(p_list,env);
		if(!strcmp(p_list->command->cmds[0],"pwd"))
			pwd();
		if(!strcmp(p_list->command->cmds[0],"echo"))
			ft_echo(p_list);
		courant = env;*/
	//	// printf("===== after =====\n");
		// while (courant)
		// {
		// 	printf("%s  =  %s\n", courant->key,courant->value);
		// 	courant = courant->next;
		// }
		// printf("\n");
	//	if(!strcmp(p_list->command->cmds[0],"env"))
	//		ft_env(env);
		add_history(line);
		free_lexer(lexer);
		free_list(&tmp_list);
		free_list(&lex_list);
		line = readline("minishell-1.0$ ");
	}
}