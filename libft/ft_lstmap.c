/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:17:51 by tarneld           #+#    #+#             */
/*   Updated: 2020/11/04 16:17:54 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*elem;

	new = NULL;
	if (!lst)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	while (lst)
	{
		if (lst->next)
		{
			elem = ft_lstnew(f(lst->next->content));
			if (!elem)
			{
				ft_lstclear(&new, del);
				return (NULL);
			}
			ft_lstadd_back(&new, elem);
		}
		lst = lst->next;
	}
	return (new);
}
