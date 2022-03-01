#include "../incs/includes.h"

static void	ft_execve_path(char *cmd, char **args,
		char **path, char	**environ)
{
	char		*cmd_temp;
	int			i;

	i = -1;
	while (path[++i])
	{
		cmd_temp = ft_strjoin(path[i], cmd);
		if (access(cmd_temp, X_OK) != -1)
		{
			execve(cmd_temp, args, environ);
			free(cmd_temp);
			return ;
		}
		free(cmd_temp);
	}
	if (path[0][0])
		errno = ENOENT;
}

static int	check_cmd(char *cmd)
{
	int		i;
	size_t	sp;

	if (!cmd)
		return (-1);
	i = -1;
	sp = 0;
	while (cmd[++i])
		if (cmd[i] == ' ')
			sp++;
	if (sp == ft_strlen(cmd))
		return (-1);
	return (1);
}

static void	hack(char **args, char **path, char **env)
{
	char	*cmd_p;

	cmd_p = ft_strjoin("/", args[0]);
	ft_execve_path(cmd_p, args, path, env);
	free(cmd_p);
}

int	ft_execve(char **args, char **environ)
{
	int			i;
	char		**path;

	path = NULL;
	i = -1;
	while (environ[++i])
	{
		if (ft_strncmp(environ[i], "PATH", 4) == 0)
			path = ft_split(environ[i] + 5, ':');
		if (ft_strncmp(environ[i], "PATH", 4) == 0)
			break ;
	}
	if (access(args[0], X_OK) != -1)
		execve(args[0], args, environ);
	else if (path == NULL || check_cmd(args[0]) == -1)
		errno = ENOENT;
	else if (args[0][0] == '/')
		execve(args[0], args, environ);
	else
		hack(args, path, environ);
	free_split(path);
	return (0);
}
