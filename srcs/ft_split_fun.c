#include "../incs/includes.h"

int	ft_arrlen(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	**ft_arr_dup(char **str)
{
	int		i;
	char	**ret;

	i = 0;
	if (!str)
		return (NULL);
	ret = NULL;
	ret = malloc(sizeof(char *) * (ft_arrlen(str) + 1));
	if (!ret)
		return (ret);
	while (str[i])
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	**ft_arr_pop(char **str, int num)
{
	int		i;
	int		plus;
	char	**ret;
	int		len;

	i = 0;
	plus = 0;
	len = ft_arrlen(str);
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char *) * ft_arrlen(str));
	while (str[i + plus])
	{
		if (i == len - 1)
			break ;
		if (i == num)
			plus = 1;
		ret[i] = ft_strdup(str[i + plus]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	**ft_arr_push(char **str, char *c)
{
	int		i;
	char	**ret;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_arrlen(str) + 2));
	while (str && str[i])
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ret[i] = ft_strdup(c);
	ret[i + 1] = NULL;
	return (ret);
}

void	free_split(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
	}
}
