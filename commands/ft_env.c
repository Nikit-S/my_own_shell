#include "commands.h"

int	ft_env(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		printf("%s\n", argv[i]);
		i++;
	}
	return (0);
}
