#include "commands.h"

int	ft_pwd(void)
{
	char	*temp;

	temp = getcwd(NULL, 260);
	if (!temp)
		return (1);
	write(1, temp, ft_strlen(temp));
	write(1, "\n", 1);
	free(temp);
	return (0);
}
