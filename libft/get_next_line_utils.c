/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2020/11/05 13:55:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join_free(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (ft_strlen(s1) == 0 && ft_strlen(s2) == 0)
	{
		free(s1);
		s1 = NULL;
		return (NULL);
	}
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while ((size_t)j < ft_strlen(s1))
		res[i++] = s1[j++];
	j = 0;
	while ((size_t)j < ft_strlen(s2))
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

int	ft_findchr(char *st, char c)
{
	int	i;

	i = 0;
	if (!st)
		return (-1);
	while (c != st[i])
	{
		if (st[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

static int	start_num(char *st)
{
	int	i;

	i = 1;
	while (st[i - 1] && st[i - 1] != '\n')
		i++;
	return (i);
}

void	divide_static(char **st)
{
	char	*temp;
	int		i;
	int		j;

	j = 0;
	if (!(**st))
		return ;
	i = start_num(*st);
	if ((ft_strlen(*st) - i + 1) + 1 <= 1)
	{
		free(*st);
		return ;
	}
	temp = malloc(sizeof(char) * ((ft_strlen(*st) - i + 1) + 1));
	if (!temp)
	{
		free(*st);
		return ;
	}
	while ((*st)[i])
		temp[j++] = (*st)[i++];
	temp[j] = '\0';
	free(*st);
	*st = temp;
}

void	unite_stnext(char **line, char **st)
{
	int		i;

	i = 0;
	if (!(*st))
		return ;
	while ((*st)[i] && (*st)[i] != '\n')
		i++;
	*line = malloc(sizeof(char) * (i + 1));
	if (!(*line))
	{
		free(*st);
		return ;
	}
	i = 0;
	while ((*st)[i] && (*st)[i] != '\n')
	{
		(*line)[i] = (*st)[i];
		i++;
	}
	(*line)[i] = '\0';
}
