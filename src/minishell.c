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
	int id;
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
			if (err == 1)
			{
				p_list = ft_parser(lex_list, hdoc_input);
				int pid = 0;

				init_fds(p_list);
				set_pipes(p_list);
				t_parser *cureent = p_list;
				if (in_builtins(p_list) && !p_list->next)
					builtins(p_list, env, 0);
				else
				{
					while (p_list)
					{
						pid = fork();
						if(!pid)
						{
							if (in_builtins(p_list))
								builtins(p_list, env, 1);
							execute_cmd(p_list, env , envp, pid);
						}
						else if(p_list->command->pipe_fd.to_close && p_list->command->pipe_fd.to_close != 1)
								close(p_list->command->pipe_fd.to_close);
						p_list = p_list->next;
					}
					while (cureent)
					{
						if(cureent->command->pipe_fd.to_close && cureent->command->pipe_fd.to_close !=1)
							close(cureent->command->pipe_fd.to_close);
						if(cureent->command->pipe_fd.write !=1 )
							close(cureent->command->pipe_fd.write);
						if(cureent->command->pipe_fd.read != 0 )
							close(cureent->command->pipe_fd.read);
						cureent =cureent->next;
					}
					while(waitpid(-1, &status, 0) != -1);
				}
				add_history(line);
				free_plist(&p_list);
			}
		}
		free_list(&lex_list);
		free_list(&tmp_list);
		free_lexer(lexer);
		if (hdoc_input)
			free(hdoc_input);
		line = readline("minishell-1.0$ ");
	}
	return (0);
}
