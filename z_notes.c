
// cat | ls

// unset PATH


// cat << a << b << c | wc -l << a		:	wc -l reads from << c instead of << a

// << a 	SEGV in executor (when no cmd)

// should fix expand	:		echo "$USER$USER"


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

 /*
 NEW ERRORS

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
