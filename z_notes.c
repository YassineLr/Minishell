
// cat | ls

// unset PATH

/*

	signals and exit_status


	minishell-1.0$ < $a
	minishell: ambiguous redirect
	could not execve
	minishell-1.0$ < "$a"
	minishell: : No such file or directory
	could not execve
	minishell-1.0$ expand a="ls -la"
	expand: a=ls -la: No such file or directory
	minishell-1.0$ export a="ls -la"
	minishell-1.0$ $a
	total 112
	drwxr-xr-x   9 oubelhaj  2019    306 Aug  1 05:02 .
	drwxr-xr-x  10 oubelhaj  2019    340 Aug  1 05:01 ..
	drwxr-xr-x  12 oubelhaj  2019    408 Aug  1 05:01 .git
	-rw-r--r--   1 oubelhaj  2019   3578 Aug  1 05:01 Makefile
	drwxr-xr-x   6 oubelhaj  2019    204 Aug  1 05:01 includes
	-rwxr-xr-x   1 oubelhaj  2019  40016 Aug  1 05:02 minishell
	-rwxr-xr-x   1 oubelhaj  2019   6189 Aug  1 05:01 minishell.h
	drwxr-xr-x   7 oubelhaj  2019    238 Aug  1 05:02 src
	-rw-r--r--   1 oubelhaj  2019    440 Aug  1 05:01 z_notes.c
	minishell-1.0$ export a="ls -la"
	minishell-1.0$ < $a
	minishell: : No such file or directory
	could not execve
	minishell-1.0$ < "$a"
	minishell: �p��: No such file or directory
	could not execve
*/





/*
	int x;
	while (p_list)
	{
		x = -1;
		while (p_list->command->cmds[++x])
			printf("cmds[%d]  : %s\n", x, p_list->command->cmds[x]);
		printf("pipe     : %d\n", p_list->command->pipe);
		printf("red_in   : %d\n", p_list->command->red_in);
		printf("red_out  : %d\n", p_list->command->red_out);
		p_list = p_list->next;
	}

	if cmd[0] == NULL dont print any error message
	if cmd[0][0] == '\0' print command not found
*/