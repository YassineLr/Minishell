
#include "../../minishell.h"


t_vars	*initialize_vars(t_list *list)
{
	t_vars	*vars;

	vars = init_vars();
	vars->expand = 1;
	vars->pipe_count = count_ends(list);
	vars->ends = malloc(sizeof(int *) * vars->pipe_count);
	if (!vars->ends)
		return (0);
	return (vars);
}

int	setup_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_count)
	{
		vars->ends[i] = malloc(sizeof(int) * 2);
		if (!vars->ends[i] || pipe(vars->ends[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

void    skip_to_next_cmd(t_list **list)
{
	while (*list && (*list)->token->type != PIPE)
		*list = (*list)->next;
	if (*list)
		*list = (*list)->next;
}

void    open_heredoc(t_list **list, t_vars *vars, t_env *env, t_hdc *hdc)
{

	*list = (*list)->next;
	if (is_quotes((*list)->token->type))
	{
		vars->expand = 0;
		*list = (*list)->next;
	}
	while (1)
	{
		if (!vars->count || !vars->count_hdcs)
			break ;
		vars->hdoc_line = readline("> ");
		if (!vars->hdoc_line)
			break ;
		if (ft_strcmp(vars->hdoc_line, (*list)->token->value))
		{
			if (vars->count == 1)
			{
				if (vars->expand == 0)
					ft_putendl_fd(vars->hdoc_line, vars->ends[vars->i][1]);
				else
					heredoc_expand(vars->hdoc_line, env, vars->ends[vars->i][1]);
			}
		}
		else
			break ;
		if (vars->hdoc_line)
			free(vars->hdoc_line);
	}
}
void    process_heredoc(t_list **list, t_vars *vars, t_env *env, t_hdc *hdc)
{
    char    *hdoc_line;

    while (*list && (*list)->token && (*list)->token->type != PIPE && vars->count_hdcs > 0)
	{
		if ((*list)->token->type == HEREDOC)
		{
            open_heredoc(list, vars, env, hdc);
			if (vars->count == 1)
				vars->i++;
			if (hdoc_line)
				free(hdoc_line);
			vars->count--;
			vars->count_hdcs--;
		}
		else
			*list = (*list)->next;
	}
}

void    close_hdc_pipes(t_vars *vars)
{
    int i;

	i = 0;
	while (i < vars->pipe_count)
	{
		close(vars->ends[i][1]);
		i++;
	}
	exit(exitcode);
}

void	child_process(t_list *list, t_vars *vars, t_env *env, t_hdc *hdc)
{
	setup_child_process(list, vars);
	while (list && vars->count_hdcs > 0)
	{
		vars->count = heredoc_count2(list);
        if (vars->count)
            skip_to_next_cmd(&list);
        else
            process_heredoc(&list, vars, env, hdc);
	}
	close_hdc_pipes(vars);
	exit(exitcode);
}

void	parent_process(t_vars *vars, t_hdc *hdc)
{
    int i;

	i = 0;
	while(waitpid(-1, &vars->status, 0) != -1)
		exit_status(vars->status);
	while (i < vars->pipe_count)
	{
		close(vars->ends[i][1]);
		i++;
	}
	i = 0;
	while (i < vars->pipe_count)
	{
		hdc->fds[i] = vars->ends[i][0];
		i++;
	}
	
}

t_hdc	*here_doc(t_list *list, t_env *env)
{
	t_hdc	*hdc;
	t_vars	*vars;

	vars = initialize_vars(list);
	if (!vars)
		return (0);
	if (!setup_pipes(vars))
		return (0);
	vars->count_hdcs = heredoc_count(list);
	if (!vars->count_hdcs)
		return (0);
	hdc = init_hdc(vars->pipe_count);
	if (!hdc)
		return (0);
	vars->pid = fork();
	if (!vars->pid)
		child_process(list, vars, env, hdc);
	else
		parent_process(vars, hdc);
	return (hdc);
}
