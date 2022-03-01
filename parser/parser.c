#include "../incs/includes.h"

static t_parser	**add_new_par(t_parser **par, int *n)
{
	t_parser	**temp;
	int			i;

	temp = malloc(sizeof(t_parser *) * (*n + 2 + 1));
	if (!temp)
		return (0);
	i = 0;
	while (par && par[i])
	{
		temp[i] = par[i];
		i++;
	}
	temp[i] = malloc(sizeof(t_parser));
	temp[i]->args = NULL;
	temp[i]->inf = NULL;
	temp[i]->outf = NULL;
	temp[i + 1] = NULL;
	free(par);
	*n += 1;
	return (temp);
}

static t_parser	**create_par0(char **str)
{
	t_parser	**par;

	par = NULL;
	if (str && str[0])
	{
		par = malloc(sizeof(t_parser *) * 2);
		par[0] = malloc(sizeof(t_parser));
		par[0]->args = NULL;
		par[0]->inf = NULL;
		par[0]->outf = NULL;
		par[1] = NULL;
	}
	return (par);
}

static t_parser	**cicle_parser(char **str, int *fl)
{
	t_parser	**par;
	int			i;
	int			k;

	i = 0;
	k = 0;
	par = create_par0(str);
	while (str && str[i] && *fl)
	{
		if (ft_strncmp(str[i], "|", ft_strlen(str[i])) == 0)
			par = add_new_par(par, &k);
		else if (ft_strncmp(str[i], "<", ft_strlen(str[i])) == 0)
			*fl = add_new_infile(par[k], str, &i);
		else if (ft_strncmp(str[i], "<<", ft_strlen(str[i])) == 0)
			*fl = add_new_infile(par[k], str, &i);
		else if (ft_strncmp(str[i], ">", ft_strlen(str[i])) == 0)
			*fl = add_new_outfile(par[k], str, &i);
		else if (ft_strncmp(str[i], ">>", ft_strlen(str[i])) == 0)
			*fl = add_new_outfile(par[k], str, &i);
		else
			*fl = add_args(par[k], str, &i);
		i++;
	}
	return (par);
}

t_parser	**ft_parser(char **str)
{
	t_parser	**par;
	int			fl;

	if (!str)
		return (NULL);
	fl = 1;
	par = cicle_parser(str, &fl);
	if (fl == 0)
	{
		free_parser(par);
		return (NULL);
	}
	return (par);
}
