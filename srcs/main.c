#include "../incs/includes.h"

int	g_sig = 2;

static int	hack(t_param *param)
{
	if (ft_strlen(skip_space(param->line, " ")) == 0)
		return (1);
	if (ft_strlen(skip_space(param->line, " ")) != 0)
		add_history(param->line);
	if (ft_strchr(param->line, '$'))
		ft_change_dol(param);
	return (0);
}

static int	do_cmds(t_param *param)
{
	int			pid;
	char		**args;

	if (hack(param))
		return (param->lret);
	args = ft_lexer(param->line);
	param->pars_tbl = ft_parser(args);
	free_split(args);
	if (param->pars_tbl && param->pars_tbl[0] && ft_sp_fun(param))
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, &sig_int_exit);
			param->lret = ft_piping(param, 0);
			free_parser(param->pars_tbl);
			free_split(param->env);
			exit (param->lret / 256);
		}
		signal(SIGINT, &sig_quit);
		wait(&param->lret);
		signal(SIGINT, &sig_int);
	}
	free_parser(param->pars_tbl);
	return (param->lret);
}

static void	cicle_status(t_param *param)
{
	while (param->status)
	{
		param->line = readline("sh> ");
		if (!check_line(param->line) && g_sig > 1)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			param->status = 0;
			g_sig = -1;
		}
		if (g_sig > 0)
			param->lret = do_cmds(param);
		free(param->line);
		if (g_sig == -1)
			break ;
		g_sig = 2;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_param	param;

	printf("Hi there, welcome to cucaracha minishell\n");
	param.env = ft_arr_dup(env);
	param.vars = NULL;
	param.status = 1;
	param.lret = 0;
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	cicle_status(&param);
	if (param.lret == -1)
		printf("invalid exit status\n");
	if (param.lret == -1)
		param.lret = 1;
	if (!param.status)
		printf("goodbuy!\n");
	rl_clear_history();
	free_split(param.env);
	free_split(param.vars);
	return (param.lret);
	(void)argc;
	(void)argv;
}
