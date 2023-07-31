
// cat | ls

// unset PATH

/*

	signals and exit_status

	add functions is_quotes and is_redirection

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
*/