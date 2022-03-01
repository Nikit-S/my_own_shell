#include "../incs/includes.h"

static int	check_sign(char *str, int *i)
{
	*i = 0;
	if (str[*i] == '-' || str[*i] == '+')
	{
		(*i)++;
		if (str[*i - 1] == '-')
			return (-1);
	}
	return (1);
}

int	value_exit(char **str)
{
	int					i;
	unsigned long long	num;
	unsigned long long	max;
	int					m;

	num = 0;
	max = 9223372036854775808u;
	if (ft_arrlen(str) == 2)
		return (-2);
	m = check_sign(str[0], &i);
	while (str[0][i])
	{
		if (!ft_isdigit(str[0][i]))
			return (-1);
		num = num * 10 + (str[0][i] - 48);
		if (num > max || (num > max - 1 && m == 1))
			return (-1);
		i++;
	}
	num = num % 256;
	if (m == 1)
		return (num);
	if (num == 0)
		return (num);
	return (256 - num);
}
