#include "../incs/includes.h"

int	read_input(char *br)
{
	char	*line;
	int		pipefd[2];

	line = NULL;
	pipe(pipefd);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, br, ft_strlen(br) + 1))
			break ;
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		write(pipefd[1], "\n", 1);
	}
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}
