/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barcher <barcher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:55:54 by barcher           #+#    #+#             */
/*   Updated: 2021/04/17 15:22:43 by barcher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*cleaner(char **ret, char **mov)
{
	while (ret[0] != *mov)
	{
		free(*mov);
		mov--;
	}
	free(*mov);
	return (NULL);
}

static int	wordcount(char const *s, char c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			ret++;
		i++;
	}
	return (ret);
}

static int	nf(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		i;
	char	**mov;

	i = 0;
	if (!s)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!ret)
		return (NULL);
	mov = ret;
	while (s[i])
	{
		if (s[i] != c)
		{
			*mov = ft_substr(s, i, nf(s + i, c));
			if (!(*mov))
				return (cleaner(ret, mov));
			mov++;
			i += nf(s + i, c) - 1;
		}
		i++;
	}
	*mov = NULL;
	return (ret);
}
