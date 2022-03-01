#include "../incs/includes.h"

void	free_parser(t_parser **par)
{
	int	i;

	i = 0;
	if (par == NULL)
		return ;
	while (par && par[i])
	{
		free_split(par[i]->args);
		if (par[i]->inf != NULL)
			close(*(par[i]->inf));
		free(par[i]->inf);
		if (par[i]->outf != NULL)
			close(*(par[i]->outf));
		free(par[i]->outf);
		free(par[i]);
		i++;
	}
	free(par);
}

int	check_quotes(char **str)
{
	int		i;
	int		ret;
	char	c;
	char	*temp;

	i = 0;
	c = 0;
	temp = 0;
	ret = 0;
	while ((*str)[i])
	{
		if (!c && ((*str)[i] == '\'' || (*str)[i] == '\"'))
		{
			c = (*str)[i];
			ret = 1;
		}
		else if (c == (*str)[i])
			c = 0;
		else
			add_char(&temp, (*str)[i]);
		i++;
	}
	free(*str);
	*str = temp;
	return (ret);
}

int	add_args(t_parser *par, char **str, int *n)
{
	char	**temp;

	check_quotes(&(str[*n]));
	if (par->args == 0)
	{
		par->args = malloc(sizeof(char *) * 2);
		par->args[0] = ft_strdup(str[*n]);
		par->args[1] = NULL;
	}
	else
	{
		temp = ft_arr_push(par->args, str[*n]);
		free_split(par->args);
		par->args = temp;
	}
	return (1);
}

int	add_new_infile(t_parser *par, char **str, int *n)
{
	int	qt;
	int	i;

	i = 0;
	if (par->inf != NULL)
		close(*(par->inf));
	if (!str[*n + 1])
		return (0);
	qt = check_quotes(&(str[*n + 1]));
	while (!qt && str[*n + 1][i] != 0)
	{
		if (ft_strchr(BADFILENAME, str[*n + 1][i]) != 0)
			return (0);
		i++;
	}
	if (par->inf == NULL)
		par->inf = malloc(sizeof(int));
	if (ft_strlen(str[*n]) == 2)
		*(par->inf) = read_input(str[*n + 1]);
	else
		*(par->inf) = open(str[*n + 1], O_RDONLY);
	*n += 1;
	return (1);
}

int	add_new_outfile(t_parser *par, char **str, int *n)
{
	int	qt;
	int	i;

	i = 0;
	if (par->outf != NULL)
		close(*(par->outf));
	if (!str[*n + 1])
		return (0);
	qt = check_quotes(&(str[*n + 1]));
	while (!qt && str[*n + 1][i] != 0)
	{
		if (ft_strchr(BADFILENAME, str[*n + 1][i]) != 0)
			return (0);
		i++;
	}
	if (par->outf == NULL)
		par->outf = malloc(sizeof(int));
	if (ft_strlen(str[*n]) == 1)
		*(par->outf) = open(str[*n + 1],
				O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else
		*(par->outf) = open(str[*n + 1], O_CREAT | O_WRONLY | O_APPEND, 0664);
	*n += 1;
	return (1);
}
