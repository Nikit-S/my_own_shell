#include "../incs/includes.h"
#include "../commands/commands.h"

char	*find_command(char *str)
{
	char	*temp;

	temp = str;
	if (!ft_strchr("<>", skip_space(temp, " ")[0]))
		return (ft_substr(temp, 0, ft_strlen(temp)
				- ft_strlen(skip_not_space(temp, "<>"))));
	while (temp && (ft_strchr(temp, '>') || ft_strchr(temp, '<')))
	{
		temp = skip_space(temp, "<> ");
		temp = skip_not_space(temp, "<> ");
		temp = skip_space(temp, " ");
		if (!ft_strchr("<>", *temp))
			return (ft_substr(temp, 0, ft_strlen(temp)
					- ft_strlen(skip_not_space(temp, "<>"))));
	}
	return (ft_substr(temp, 0, ft_strlen(temp)
			- ft_strlen(skip_not_space(temp, "<>"))));
}

static int	ft_sh_fun(t_param *param, int i_c)
{
	int		st;
	char	*str;

	st = 1;
	(void) i_c;
	str = param->pars_tbl[i_c]->args[0];
	if (!ft_strncmp(str, "echo", 5))
		st = ft_echo(param->pars_tbl[i_c]->args);
	else if (!ft_strncmp(str, "pwd", 4))
		st = ft_pwd();
	else if (!ft_strncmp(str, "env", 4))
		st = ft_env(param->env);
	return (st);
}

int	ft_child(t_param *param, int pipefd[2], int i_c)
{
	close(pipefd[0]);
	if (param->pars_tbl[i_c + 1] && param->pars_tbl[i_c]->outf == NULL)
		dup2(pipefd[1], 1);
	if ((param->pars_tbl[i_c]->inf && *(param->pars_tbl[i_c]->inf) == -1)
		|| (param->pars_tbl[i_c]->outf && *(param->pars_tbl[i_c]->outf) == -1))
		return (1);
	if (param->pars_tbl[i_c]->inf)
		dup2(*(param->pars_tbl[i_c]->inf), 0);
	if (param->pars_tbl[i_c]->outf)
		close(pipefd[1]);
	if (param->pars_tbl[i_c]->outf)
		dup2(*(param->pars_tbl[i_c]->outf), 1);
	if (ft_sh_fun(param, i_c))
		ft_execve(param->pars_tbl[i_c]->args, param->env);
	if (param->pars_tbl[i_c]->inf)
		close(*(param->pars_tbl[i_c]->inf));
	if (param->pars_tbl[i_c]->outf)
		close(*(param->pars_tbl[i_c]->outf));
	close(pipefd[1]);
	return (0);
}

int	ft_piping(t_param *param, int i_c)
{
	int	pipefd[2];
	int	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == -1)
		ft_perror("pid");
	if (pid == 0)
	{
		if (ft_child(param, pipefd, i_c) || errno)
			exit (1);
		exit (0);
	}
	else
	{
		close(pipefd[1]);
		if (param->pars_tbl[i_c + 1] && !param->pars_tbl[i_c + 1]->inf)
			dup2(pipefd[0], 0);
		if (param->pars_tbl[i_c + 1] && param->pars_tbl[i_c + 1]->args)
			ft_piping(param, i_c + 1);
		close(pipefd[0]);
		wait(&(param->lret));
		return (param->lret);
	}
}
