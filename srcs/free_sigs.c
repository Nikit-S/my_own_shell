#include "../incs/includes.h"

void	sig_quit(int code)
{
	(void)code;
	g_sig = 2;
}

void	sig_int(int code)
{
	(void)code;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_int_exit(int code)
{
	(void)code;
	printf("\n");
	exit(0);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		i++;
		if (line[i] == 0)
			return (1);
		if (line[i] == '\n')
			return (2);
	}
	return (1);
}
