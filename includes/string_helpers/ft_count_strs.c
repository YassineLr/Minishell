#include "../../minishell.h"

int	ft_count_strs(char **str)
{
	int	i;
	
	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
