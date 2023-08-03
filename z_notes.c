
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

	send last heredoc of every command (before pipe), instead of last command line


 /*
 NEW ERRORS
export a="asdf asdf asdd fas"
bash-3.2$ ls $a
ls: asdd: No such file or directory
ls: asdf: No such file or directory
ls: asdf: No such file or directory
ls: fas: No such file or directory
*******
syntax error should be added to history
*******
export a=asdfsadf
export a
declare -x a="a asdf sa fsd"
declare -x a
********
minishell-1.0$ unset OLDPWD
minishell-1.0$ cd -
cd: No such file or directory
minishell-1.0$ unset PWD
minishell-1.0$ cd includes
[1]    28861 segmentation fault  ./minishell
*********
minishell-1.0$ cd includes
minishell-1.0$ unset PWD
minishell-1.0$ cd -
cd: No such file or directory
minishell-1.0$ unset OLDPWD
minishell-1.0$ cd -
cd: No such file or directory
*********
bash-3.2$ expr $? + $?
2
bash-3.2$ expr $? + $?
0
bash-3.2$ expr $? + $?
2
bash-3.2$ expr $? + $?
0
bash-3.2$ expr $? + $?
2
bash-3.2$ expr $? + $?
0
bash-3.2$ expr $? + $?
2
bash-3.2$ expr $? + $?
0
*/
