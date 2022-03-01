#ifndef PARSER_H
# define PARSER_H
# include "../incs/includes.h"
# define BADFILENAME "\'\"!@#$%^&*()<>,:;{}\\?/+=|"

typedef struct s_parser
{
	char	**args;
	int		*inf;
	int		*outf;
}				t_parser;

void	free_parser(t_parser **par);
int		add_args(t_parser *par, char **str, int *n);
int		add_new_infile(t_parser *par, char **str, int *n);
int		add_new_outfile(t_parser *par, char **str, int *n);

#endif
