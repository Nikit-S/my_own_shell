#include "../incs/includes.h"

int	*add_char(char **str, char c)
{
	char	*temp;
	char	*aloc_c;

	aloc_c = malloc(sizeof(char) * 2);
	aloc_c[0] = c;
	aloc_c[1] = 0;
	if (*str == NULL)
		temp = ft_strdup(aloc_c);
	else
		temp = ft_strjoin(*str, aloc_c);
	free(*str);
	*str = ft_strdup(temp);
	free(temp);
	free(aloc_c);
	return (0);
}

int	ft_tres_action(t_tres *tres)
{
	int	i;

	i = 0;
	tres->temp2 = ft_strjoin(tres->temp, tres->replace);
	free(tres->temp);
	free(tres->replace);
	tres->temp = tres->temp2;
	i = ft_strlen(tres->var) + 1;
	return (i);
}

int	choose_replace(t_param *param, t_tres *tres, int i)
{
	tres->replace = NULL;
	if (param->line[i + 1] == '?')
		tres->replace = ft_itoa(param->lret / 256);
	else if (!ft_check_var_env(param, tres->var))
		return (1);
	else if (ft_check_var_env(param, tres->var))
		tres->replace = ft_strdup(ft_check_var_env(param, tres->var)
				+ ft_strlen(tres->var) + 1);
	return (0);
}

int	decide_fl(char *str, int n, int (*fl)[2])
{
	int	i;

	i = n + 1;
	if (str[n] == '\"')
		(*fl)[1] *= -1;
	if (str[n] == '\'' && (*fl)[1] > 0)
	{
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] == '\'' || (*fl)[0] < 0)
			(*fl)[0] *= -1;
	}
	if ((*fl)[0] > 0)
		return (1);
	return (0);
}

int	ft_change_dol(t_param *param)
{
	t_tres	tres;
	int		i;
	int		fl[2];

	fl[0] = 1;
	fl[1] = 1;
	i = 0;
	init_tres(&tres);
	while (param->line[i])
	{
		if (decide_fl(param->line, i, &fl) && param->line[i] == '$')
		{
			tres.var = get_var(param->line + i + 1);
			choose_replace(param, &tres, i);
			i += ft_tres_action(&tres);
			free(tres.var);
			continue ;
		}
		add_char(&tres.temp, param->line[i]);
		i++;
	}
	free(param->line);
	param->line = ft_strdup(tres.temp);
	free(tres.temp);
	return (0);
}
