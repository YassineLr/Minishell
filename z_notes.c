
// cat | ls

// unset PATH

/*
	bash-3.2$	export a="a b d"
	bash-3.2$	< $a
	bash: $a:	ambiguous redirect
	bash-3.2$	< "$a"
	bash: a b d: No such file or directory
	bash-3.2$
*/
