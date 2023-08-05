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
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

int exitcode;

typedef struct s_hdc
{
	int	*fds;
	int	count;
}	t_hdc;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env *next;
}	t_env;

typedef struct s_lexer
{
	int		i;
	char	c;
	char	*content;
}	t_lexer;

typedef struct s_token
{
	enum
	{
		WORD,
		PIPE,
		S_QUOTES,
		D_QUOTES,
		RED_IN,
		RED_OUT,
		WHITESPACE,
		APPEND,
		HEREDOC,
	}	type;
	char	*value;
	int		expanded;
	int		in_quotes;
}	t_token;

typedef struct s_list
{
	t_token			*token;
	struct s_list	*next;
}	t_list;

typedef struct s_pipe
{
	// int to_close;
	int write;
	int read;
}	t_pipe;

typedef struct s_reds
{
	int				fd;
	struct s_reds	*next;
}	t_reds;

typedef struct s_cmd
{
	char		**cmds;
	int			pipe;
	t_pipe		pipe_fd;
	int			red_in;
	int			red_out;
}	t_cmd;

typedef struct s_parser
{
	t_cmd			*command;
	struct s_parser	*next;
}	t_parser;

typedef struct s_vars
{
	int		expand;
	int		in_quotes;
	int		flag;
	char	*tmp;
	int		prev;
}	t_vars;

// Readline
int rl_replace_line(const char *text, int clear_undo);

// Error handling
int		check_errors(char *input, t_list *list);
int		check_quotes(char *input);
int		check_end(char *input);
int		check_redirections(t_list *list);
int		redirections(t_list *list, int red_type);
int		check_pipes(t_list *list);

// Linked lists
t_list		*ft_lstnew(t_token *token);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
int			ft_lstsize(t_list *lst);
void		ft_lstclear(t_list **lst, void (*del)(void*));
t_parser	*ft_lstnew_alt(t_cmd *cmd);
void		ft_lstadd_back_alt(t_parser **lst, t_parser *new);
t_parser	*ft_lstlast_alt(t_parser *lst);
t_env		*ft_lstnew_env(char **enviroment);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_last_env(t_env *lst);
void		ft_lstclear_env(t_env **lst, void (*del)(void*));
void		ft_lstdelone_env(t_env *lst, void (*del)(void *));
t_reds		*ft_lstlast_reds(t_reds *lst);
t_reds		*ft_lstnew_reds(int fd);
void		ft_lstadd_back_reds(t_reds **lst, t_reds *new);
void		ft_lstclear_reds(t_reds **lst);

// Lexer
void	ft_lexer(t_lexer *lexer, t_list **list, t_env *env);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespaces(t_lexer *lexer);
char	*lexer_char_to_string(char c);
void	lexer_handle_dollar(t_lexer *lexer, t_list **list);
char	*get_word(t_lexer *lexer);
void	lexer_handle_single_quotes(t_lexer *lexer, t_list **list);
void	lexer_handle_double_quotes(t_lexer *lexer, t_list **list);
void	lexer_handle_input_redirection(t_lexer *lexer, t_list **list);
void	lexer_handle_output_redirection(t_lexer *lexer, t_list **list);
void	lexer_handle_pipe(t_lexer *lexer, t_list **list);
void	lexer_handle_whitespace(t_lexer *lexer, t_list **list);
t_list	**join_words(t_list **list, t_list *tmp_list);
void	remove_type(t_list **head, int type);
void	remove_nulls(t_list **head);

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
t_env	*search_in_env(t_env *env, char *key);
int		is_quotes(int type);
int		is_redir(int type);
int		is_redir_2(int type);

// String helpers
void	ft_free_strs(char **str);
int		index_at(char *str, char c);
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
int		ft_count_strs(char **str);
char	*ft_itoa(int n);

// Expansion
void	expansion(t_list *list, t_env *env);
int		must_expand(char *str);
void	mark_quotes(t_list **list, t_vars *vars);
void	handle_expand(t_list **list, t_vars *vars, t_env *env);
char	*expand_(char *str, t_env *env);
char	*expand_regular_text(char *str, int *i);
void	expansion_v2(char *str, t_env *env, int fd);
char	*expand_dollar_sign(char *str, t_env *env, int *i);
char	*expand_env_variable(char *str, t_env *env, int *i);

// heredoc
t_hdc	*here_doc(t_lexer *lexer, t_list *list, t_env *env);
int		handle_heredoc(t_list **list, int prev_type);
int		heredoc_count(t_list *list);
int		hc_handle_errors(int prev_type, int curr_type);

// get_next_line
char	*fill_buff(int fd);
char	*get_next_line(int fd);
char	*fill_and_join(int fd, char **saved, char *line, char *tmp);

// Parser
t_parser	*ft_parser(t_list *list, t_hdc *hdc);

// init
t_vars	*init_vars(void);
t_cmd	*init_cmd(void);
t_vars	*init_vars(void);
t_lexer	*init_lexer(char *content);
t_token *init_token(int type, char *value);

// Files
int	open_append(t_list *list);
int	open_redout(t_list *list);
int	open_redin(t_list *list);
int	file_error(char *filename);
int	check_filename(char *name);

// freeing
void	free_list(t_list **list);
void	free_plist(t_parser **list);
void	free_hdc(t_hdc *hdc);
void	free_lexer(t_lexer *lexer);

// Signals
int		signals_handler(char *line);

//builtins

void	go_home(t_env *env);
void	cd(t_parser *parse ,t_env *env);
void	export(t_parser *parse, t_env **env);
void 	ft_env(t_env *env);
void    unset(t_parser *parse, t_env *env);
void 	pwd(void);
void    ft_echo(t_parser *parse);
int 	in_builtins(t_parser *parse);
void 	builtins(t_parser *parse, t_env *env, int child);

void   	execute_cmd(t_parser *parse, t_env *env, char **envp);
void 	init_fds(t_parser *parse);
void    ft_dup(t_parser *parse);
t_env	*get_env(char **envp);
void 	set_pipes(t_parser *parse);
char 	**env_in_tab(t_env *env);
void	exit_status(int status);
void	close_pipes(t_parser *parse, int fread, int fwrite);
void 	executor(t_parser *parse, t_env *env, char **envp);
void	ft_exit(t_parser *parse);

void	print_error(char *error);
void 	command_nf_error(t_parser *parse);
void	redirection(t_parser *parse);
void	close_files(t_parser *parse);
void 	no_path_err(t_parser *parse);


#endif
