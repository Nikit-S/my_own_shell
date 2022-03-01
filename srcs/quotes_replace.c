#include "../incs/includes.h"

void	replace_in_line(char **str, int start, int *end, char *fragm)
{
	char	*new;
	int		i;

	new = NULL;
	i = 0;
	if (ft_strlen(fragm) != 0)
	{
		new = ft_substr(*str, 0, start);
		new = ft_join_free(new, fragm);
		i = ft_strlen(new);
		new = ft_join_free(new, *str + *end + 1);
		free(*str);
		*str = new;
	}
	else
	{
		*str = malloc(sizeof(char) * 1);
		(*str)[0] = 0;
	}
	*end = i;
	if (*end)
		*end -= 1;
}

char	*replace_filename(char *str, t_param param)
{
	int		j;
	int		k;
	char	*res;

	j = 0;
	res = NULL;
	while (str[j])
	{
		if (str[j] == '\"')
		{
			k = j;
			j++;
			while (str[j] && str[j] != '\"')
				j++;
			res = param.quotes[ft_atoi(str + k + 1)];
			return (res);
		}
		j++;
	}
	return (res);
}

static int	hack(char *str, int i)
{
	int	ret;

	ret = 0;
	while (str[i + ret] && str[i + ret] != '\"')
		ret++;
	return (ret);
}

void	replace_quotes(char **str, t_param param)
{
	int	a[3];

	a[0] = -1;
	while (str && str[++a[0]])
	{
		a[1] = -1;
		while (str[a[0]][++a[1]])
		{
			if (str[a[0]][a[1]] == '\"')
			{
				a[2] = a[1]++;
				a[1] += hack(str[a[0]], a[1]);
				if (!str[a[0]][a[1]])
					break ;
				if (param.quotes && param.quotes[ft_atoi(str[a[0]] + a[2] + 1)])
					replace_in_line(&(str[a[0]]), a[2], &a[1],
						param.quotes[ft_atoi(str[a[0]] + a[2] + 1)]);
				else
				{
					replace_in_line(&(str[a[0]]), a[2], &a[1], "\0");
					break ;
				}
			}
		}
	}
}
