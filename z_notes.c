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

			while (lex_list)
			{
				printf("type : %d\nvalue :%s\n\n", lex_list->token->type, lex_list->token->value);
				lex_list = lex_list->next;
			}
			exit(1);



	export A-

	exit +100
	exit "+100"

	exit +"100"

	exit 9223372036854775808



	ls | << a /bin/cat < Makefile  | /bin/cat -e
	cat << a < Makefile| cat << b << c | cat << d
	> fsdfsdf
	> a
	> b
	> v
	> sdgsdgsdgc
	> c
	> fgdfgdfgdfgdf
	v
	sdgsdgsdgc

	double free in this case : export jjj+=od 

	minishell-1.0$ cd includes/
	minishell-1.0$ cd dfghjkl;
	cd: No such file or directory
	minishell-1.0$ cd dfghjkl;
	cd: No such file or directory
	minishell-1.0$ cd
	minishell-1.0$ cd ..
	minishell-1.0$ cd
	minishell-1.0$ cd -
	minishell-1.0$ cd ~
	minishell-1.0$ pwd
	/Users/ylarhris
	minishell-1.0$ ls
	Applications	Downloads	goinfre
	Desktop		Library
	Documents	Music
	minishell-1.0$ cd Desktop/
*/
