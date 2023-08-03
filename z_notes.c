
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
				}

*/