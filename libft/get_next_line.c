/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:55:06 by tarneld           #+#    #+#             */
/*   Updated: 2020/11/05 13:55:10 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	read_in_buff(int fd, char **s, char **buff, int *n)
{
	*n = 1;
	while (ft_findchr(*s, '\n') < 0 && *n > 0)
	{
		*n = read(fd, *buff, BUFFER_SIZE);
		if (*n < 0)
		{
			free(s[fd]);
			free(*buff);
			return (-1);
		}
		(*buff)[*n] = '\0';
		*s = ft_join_free(*s, *buff);
	}
	free(*buff);
	return (1);
}

static int	ret_val(int n)
{
	if (n == 0)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*s[1024];
	int				n;
	int				fl;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	fl = read_in_buff(fd, &s[fd], &buff, &n);
	if (fl < 0)
		return (fl);
	if (s[fd])
	{
		unite_stnext(line, &s[fd]);
		divide_static(&s[fd]);
		return (ret_val(n));
	}
	*line = malloc(sizeof(char) * 1);
	if (!(*line))
		return (-1);
	**line = '\0';
	free(s[fd]);
	return (ret_val(n));
}
