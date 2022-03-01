#include "commands.h"

int	go_home(char **env)
{
	if (env && find_var(env, "HOME=path") == -1)
		printf("HOME not set\n");
	else if (chdir(ft_strchr(env[find_var(env, "HOME=path")], '=') + 1) == -1)
		return (ft_perror("cd"));
	return (0);
}

int	tilda(char *str, char **env)
{
	char	*pwd;

	if (env && find_var(env, "HOME=path") == -1)
		printf("HOME not set\n");
	else
	{
		pwd = ft_strjoin(ft_strchr(env[find_var(env,
						"HOME=path")], '=') + 1, str);
		if (chdir(pwd) == -1)
		{
			free(pwd);
			return (ft_perror("cd"));
		}
		free(pwd);
	}
	return (0);
}

int	go_back(char **env)
{
	if (env && find_var(env, "OLDPWD=path") == -1)
		printf("OLDPWD not set\n");
	else if (chdir(ft_strchr(env[find_var(env, "OLDPWD=path")], '=') + 1) == -1)
		return (ft_perror("cd"));
	return (0);
}

int	set_oldpwd(t_param *param, char *oldpwd)
{
	char	**temp_env;
	char	*oldpwd_str;

	temp_env = ft_arr_pop(param->env, find_var(param->env, "OLDPWD=path"));
	free_split(param->env);
	oldpwd_str = ft_strjoin("OLDPWD=", oldpwd);
	param->env = ft_arr_push(temp_env, oldpwd_str);
	free_split(temp_env);
	free(oldpwd_str);
	return (0);
}

int	ft_cd(t_param *param)
{
	int		i;
	char	**argv;
	char	*oldpwd;

	argv = param->pars_tbl[0]->args;
	i = ft_arrlen(argv);
	if (i > 2)
	{
		errno = EINVAL;
		ft_perror("cd");
		errno = 0;
		return (1);
	}
	oldpwd = getcwd(NULL, 260);
	if (i == 1)
		go_home(param->env);
	else if (i == 2 && !ft_strncmp(argv[1], "~", 1))
		tilda(argv[1] + 1, param->env);
	else if (i == 2 && !ft_strncmp(argv[1], "-", 2))
		go_back(param->env);
	else if (chdir(argv[1]) == -1)
		ft_perror("cd");
	set_oldpwd(param, oldpwd);
	free(oldpwd);
	return (0);
}
