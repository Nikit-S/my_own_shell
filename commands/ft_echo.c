#include "commands.h"

static int	flag_n(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	newline_flag(char **str, int *newline)
{
	int	i;

	i = 1;
	while (str && str[i])
	{
		if (flag_n(str[i]))
			*newline = 0;
		else
			return (i);
		i++;
	}
	return (i);
}

int	ft_echo(char **argv)
{
	int	newline;
	int	i;

	newline = 1;
	i = newline_flag(argv, &newline);
	while (argv && argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
