#ifndef INCLUDES_H
# define INCLUDES_H
# define BADSYMBOLS " \'\"!@#$%^&*()><.,:;_"
# define BADFILENAME "\'\"!@#$%^&*()<>,:;{}\\?/+=|"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>
# include <string.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_parser
{
	char	**args;
	int		*inf;
	int		*outf;
}				t_parser;

typedef struct s_param
{
	int				status;
	char			*path;
	char			**env;
	char			**vars;
	char			*line;
	char			**quotes;
	int				lret;
	t_parser		**pars_tbl;
}	t_param;

typedef struct s_tres
{
	char	*replace;
	char	*temp;
	char	*temp2;
	char	*var;
}	t_tres;

extern int	g_sig;

int				*add_char(char **str, char c);
void			free_split(char **cmds);
void			sig_quit(int code);
void			sig_int(int code);
void			sig_int_exit(int code);
char			*skip_space(char *str, char *a);
char			*skip_not_space(char *str, char *a);
int				ft_perror(char *str);
int				ft_set_vars(t_param *param, char **args);
int				check_line(char *line);
int				read_input(char *br);
int				ft_in_files(char *cmds, t_param param);
char			**ft_arr_dup(char **str);
char			**ft_arr_pop(char **str, int num);
char			**ft_arr_push(char **str, char *c);
int				ft_arrlen(char **str);
int				ft_export(t_param *param);
int				value_pair(char *str);
int				find_var(char **arr, char *str);
int				ft_execve(char **args, char **environ);
char			**parse_quotes(char **line);
void			replace_in_line(char **str, int start, int *end, char *fragm);
void			replace_quotes(char **strs, t_param param);
char			*replace_filename(char *str, t_param param);
int				ft_piping(t_param *param, int i_c);
int				ft_sp_fun(t_param *param);
int				ft_change_dol(t_param *param);
char			*ft_check_var_env(t_param *param, char *var);
char			*get_var(char *str);
void			init_tres(t_tres *tres);
int				ft_out_files(char *cmds, t_param param);
char			**ft_lexer(char *str);
t_parser		**ft_parser(char **str);
void			free_parser(t_parser **par);
int				add_args(t_parser *par, char **str, int *n);
int				add_new_infile(t_parser *par, char **str, int *n);
int				add_new_outfile(t_parser *par, char **str, int *n);
int				value_exit(char **str);
#endif
