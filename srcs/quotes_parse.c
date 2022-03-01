#include "../incs/includes.h"

static char	**push_end_arr(char **str, char *c, int start, int end)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_arrlen(str) + 2));
	while (str && str[i])
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	j = 0;
	ret[i] = malloc(sizeof(char) * (end - start + 1));
	while (start + j < end)
	{
		ret[i][j] = c[start + j];
		j++;
	}
	ret[i][j] = 0;
	ret[i + 1] = NULL;
	free_split(str);
	return (ret);
}

static char	*name_quote(int num)
{
	char	*it;
	char	*res;

	it = ft_itoa(num);
	res = ft_join_free(ft_strjoin("\"", it), "\"");
	free(it);
	return (res);
}

static char	**new_quotes(int *i, char **line, char **quotes, char c)
{
	char	*name;
	int		j;

	j = *i + 1;
	(*i)++;
	while ((*line)[*i] && (*line)[*i] != c)
		(*i)++;
	if (!(*line)[*i])
	{
		return (quotes);
	}
	quotes = push_end_arr(quotes, (*line), j, *i);
	name = name_quote(ft_arrlen(quotes) - 1);
	replace_in_line(line, j - 1, i, name);
	free(name);
	return (quotes);
}

char	**parse_quotes(char **line)
{
	char	**quotes;
	int		i;

	i = 0;
	quotes = NULL;
	while ((*line)[i])
	{
		if ((*line)[i] == '\"')
			quotes = new_quotes(&i, line, quotes, '\"');
		if ((*line)[i] == '\'')
			quotes = new_quotes(&i, line, quotes, '\'');
		i++;
	}
	return (quotes);
}
