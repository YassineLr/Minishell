


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



	keep quotes and update parser based on that, to check in parser to expand heredoc delim or not

//	cat << a << b << c | echo << a

// cat | echo | export > l | env > h | echo skf sdkfmm sdmfm | wc -l
*/
