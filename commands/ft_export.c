#include "../incs/includes.h"

int	find_var(char **arr, char *str)
{
	int		i;
	char	*c;

	i = 0;
	c = skip_not_space(str, "= ");
	if (c && *c)
		c++;
	while (arr && arr[i])
	{
		if (!ft_strncmp(arr[i], str, ft_strlen(str) - ft_strlen(c)))
			return (i);
		i++;
	}
	return (-1);
}

int	compare_params(t_param *param, char **args)
{
	int	i;
	int	l;

	i = -1;
	while (param->env && param->env[++i])
	{
		l = -1;
		while (param->vars && param->vars[++l])
		{
			if (!ft_strncmp(param->env[i], param->vars[l],
					ft_strlen(param->vars[l]) + ft_strlen(param->env[i])))
				printf("%s\n", param->vars[l]);
		}
	}
	free_split(args);
	return (1);
}

static void	hack(t_param *param, char *str)
{
	char	**temp;

	temp = NULL;
	if (find_var(param->env, str) != -1 && (ft_strchr(str, '=')
			|| find_var(param->vars, str) != -1))
	{
		temp = ft_arr_pop(param->env, find_var(param->env, str));
		free_split(param->env);
		param->env = temp;
	}
}

int	ft_export(t_param *param)
{
	char	**temp;
	char	**args;
	int		l;

	args = ft_arr_dup(param->pars_tbl[0]->args);
	l = 0;
	if (ft_arrlen(args) == 1)
		return (compare_params(param, args));
	while (args && args[++l])
	{
		hack(param, args[l]);
		if (value_pair(args[l]))
			temp = ft_arr_push(param->env, args[l]);
		else if (find_var(param->vars, args[l]) != -1)
			temp = ft_arr_push(param->env,
					param->vars[find_var(param->vars, args[l])]);
		else
			temp = ft_arr_dup(param->env);
		free_split(param->env);
		param->env = temp;
	}
	free_split(args);
	return (0);
}
