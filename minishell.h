/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:40:14 by oubelhaj          #+#    #+#             */
/*   Updated: 2023/05/26 18:40:14 by oubelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_lexer
{
	int		i;
	char	c;
	char	*content;
	t_env	**env;
}	t_lexer;

typedef struct s_token
{
	enum
	{
		WORD,
		PIPE,
		RED_IN,
		RED_OUT,
		WHITESPACE,
		APPEND,
		HEREDOC,
	}	type;
	char	*value;
}	t_token;

typedef struct s_list
{
	t_token			*token;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd
{
	char	**cmds;
	int		pipe;
	int		red_out;
	int		red_in;
	int		append;
	int		*heredoc;
}	t_cmd;

typedef struct s_parser
{
	t_cmd			*command;
	struct s_parser	*next;
}	t_parser;

// Error handling
int		check_errors(char *input);
void	exit_error(char *message, int s);
int		check_end(char *input);

// Linked lists
t_list		*ft_lstnew(t_token *token);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
int			ft_lstsize(t_list *lst);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		free_list(t_list *list);
t_parser	*ft_lstnew_alt(t_cmd *cmd);
void		ft_lstadd_back_alt(t_parser **lst, t_parser *new);
t_parser	*ft_lstlast_alt(t_parser *lst);

// Lexer
t_lexer	*init_lexer(char *content, char **envp);
void	ft_lexer(t_lexer *lexer, t_list **list);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespaces(t_lexer *lexer);
char	*lexer_char_to_string(char c);
t_token *init_token(int type, char *value);
void	free_lexer(t_lexer *lexer);

// Helpers
int		ft_is_whitespace(int c);
long	ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		is_special(char c);
int		count_env(char **str);

// String helpers
void	ft_free_strs(char **str);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char const *s2);
int		ft_strlen(const char *str);
char	*ft_strchr(char *buff, char c);
int		ft_strstr(char *haystack, char *needle);
char	*ft_strnstr(const char *haystack, const char *needle, int len);
char	*get_quoted_string(t_lexer *lexer, char quotes);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, int start, int len);

// Expansion
char	*expansion(t_lexer *lexer);
t_env	**get_env(char **ev);

// get_next_line
char	*fill_buff(int fd);
char	*get_next_line(int fd);
char	*fill_and_join(int fd, char **saved, char *line, char *tmp);


int		*here_doc(char *line);
int		heredoc_count(char *input);

t_parser	*ft_parser(t_list *list, int *hdc_pipe);

int	open_append(char *filename);
int	open_redout(char *filename);
int	open_redin(char *filename);

#endif