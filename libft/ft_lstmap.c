/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:53:06 by nkolle            #+#    #+#             */
/*   Updated: 2021/08/10 12:57:07 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list_item;
	t_list	*newlist;

	newlist = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		new_list_item = ft_lstnew(f(lst->content));
		if (!new_list_item)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		if (!newlist)
			newlist = new_list_item;
		else
			ft_lstadd_back(&newlist, new_list_item);
		lst = lst->next;
	}
	return (newlist);
}
