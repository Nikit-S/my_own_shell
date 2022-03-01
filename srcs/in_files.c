#include "../incs/includes.h"

static int	ft_in_files_body(char **temp, char **filename, t_param param)
{
	int	append;

	append = 0;
	(*temp) = ft_strchr((*temp), '<');
	if ((*temp) && (*temp)[0] && (*temp)[0] == '<' && (*temp)[1]
		&& (*temp)[1] == '<' && (((*temp)[2] && (*temp)[2] != '<')
				|| (*temp)[2] == 0))
		append = 1;
	if ((*temp) == NULL)
		return (-1);
	(*temp) = skip_space((*temp), " <");
	if ((*temp)[0] == '\"')
		*filename = replace_filename((*temp), param);
	else
		*filename = ft_substr((*temp), 0, ft_strlen((*temp))
				- ft_strlen(skip_not_space((*temp), " <")));
	return (append);
}

int	ft_in_files(char *cmds, t_param param)
{
	int		i;
	char	*temp;
	int		fd;
	char	*filename;

	temp = cmds;
	while (temp)
	{
		i = ft_in_files_body(&temp, &filename, param);
		if (i == -1)
			break ;
		if (i)
			fd = read_input(filename);
		else
			fd = open(filename, O_RDONLY);
		if (fd == -1)
			ft_perror(filename);
		free(filename);
		if (ft_strchr(temp, '<') && fd != -1)
			close(fd);
	}
	if (fd != -1)
		dup2(fd, 0);
	return (fd);
}
