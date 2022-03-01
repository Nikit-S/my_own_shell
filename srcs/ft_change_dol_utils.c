#include "../incs/includes.h"

char	*ft_check_var_env(t_param *param, char *var)
{
	int	i;
	int	l;

	i = -1;
	l = -1;
	while (param->env && param->env[++i])
	{
		if (!ft_strncmp(param->env[i], var, ft_strlen(var))
			&& param->env[i][ft_strlen(var)] == '=')
			return (param->env[i]);
	}
	while (param->vars && param->vars[++l])
	{
		if (!ft_strncmp(param->vars[l], var, ft_strlen(var))
			&& param->vars[l][ft_strlen(var)] == '=')
			return (param->vars[l]);
	}
	return (NULL);
}

char	*get_var(char *str)
{
	char	*ret;

	ret = ft_substr(str, 0, ft_strlen(str) - ft_strlen(skip_not_space(str,
					BADSYMBOLS)));
	return (ret);
}

void	init_tres(t_tres *tres)
{
	tres->temp = NULL;
	tres->temp2 = NULL;
	tres->replace = NULL;
	tres->var = NULL;
}
