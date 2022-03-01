#include "../incs/includes.h"
#include "../commands/commands.h"

static int	hack(t_param *param, char *str)
{
	char	*exp;

	exp = NULL;
	if (find_var(param->env, str) != -1)
	{
		exp = ft_strdup(param->line);
		free(param->line);
		param->line = ft_strjoin("export ", str);
		ft_export(param);
		free(param->line);
		param->line = exp;
		return (1);
	}
	return (0);
}

int	ft_set_vars(t_param *param, char **args)
{
	char	**temp2;
	char	**ret;
	int		i;

	i = -1;
	while (args[++i])
		if (!value_pair(args[i]))
			return (1);
	i = -1;
	while (args[++i])
	{
		if (hack(param, args[i]))
			continue ;
		if (find_var(param->vars, args[i]) != -1)
		{
			temp2 = ft_arr_pop(param->vars, find_var(param->vars, args[i]));
			free_split(param->vars);
			param->vars = temp2;
		}
		ret = ft_arr_push(param->vars, args[i]);
		free_split(param->vars);
		param->vars = ret;
	}
	return (0);
}

int	ft_sp_fun(t_param *param)
{
	int		st;

	st = 1;
	if (param->pars_tbl[1])
		return (st);
	if (!ft_strncmp(param->pars_tbl[0]->args[0], "exit", 5))
	{
		param->status = 0;
		if (param->pars_tbl[0]->args[1]
			&& value_exit(param->pars_tbl[0]->args + 1) != -2)
			param->lret = value_exit(param->pars_tbl[0]->args + 1);
		else if (param->pars_tbl[0]->args[1])
			param->status = 1;
		st = 0;
	}
	else if (!ft_strncmp(param->pars_tbl[0]->args[0], "cd", 3))
		st = ft_cd(param);
	else if (!ft_strncmp(param->pars_tbl[0]->args[0], "unset", 6))
		st = ft_unset(&(param->env), param->pars_tbl[0]->args);
	else if (!ft_strncmp(param->pars_tbl[0]->args[0], "export", 7))
		st = ft_export(param);
	else if (ft_strchr(param->pars_tbl[0]->args[0], '='))
		st = ft_set_vars(param, param->pars_tbl[0]->args);
	return (st);
}
