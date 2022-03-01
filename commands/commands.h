#ifndef COMMANDS_H
# define COMMANDS_H

# include "../libft/libft.h"
# include "../incs/includes.h"
# include <stdio.h>
# include <errno.h>

int	ft_cd(t_param *param);
int	ft_echo(char **argv);
int	ft_pwd(void);
int	ft_env(char **argv);
int	ft_unset(char ***env, char **var);
#endif
