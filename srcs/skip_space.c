#include "../incs/includes.h"

char	*skip_space(char *str, char *a)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(a, str[i]))
			i++;
		else
			break ;
	}
	return (str + i);
}

char	*skip_not_space(char *str, char *a)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(a, str[i]))
			i++;
		else
			break ;
	}
	return (str + i);
}

int	ft_perror(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	return (1);
}

int	value_pair(char *str)
{
	if (skip_not_space(skip_space(str, " "), " =")[0] != '=' ||
			!skip_not_space(skip_space(str, " "), " =")[1])
		return (0);
	if (ft_strlen(skip_not_space(skip_not_space(skip_space(str, " "), " =") + 1,
				" ")) == 0)
		return (1);
	return (0);
}
