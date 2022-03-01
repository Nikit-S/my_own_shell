#include "commands.h"

int	ft_unset(char ***env, char **var)
{
	int		l;
	char	**temp;

	l = 1;
	if (!*env || !var)
		return (1);
	while (var[l])
	{
		temp = ft_arr_pop(*env, find_var(*env, var[l]));
		free_split(*env);
		*env = ft_arr_dup(temp);
		free_split(temp);
		l++;
	}
	return (0);
}
