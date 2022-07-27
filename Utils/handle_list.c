/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 14:52:11 by nkolle            #+#    #+#             */
/*   Updated: 2022/07/26 17:00:27 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_operator	*ft_lstlast_op(t_operator *lst)
{
	if (!lst)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_buffer	*ft_lstlast_buf(t_buffer *lst)
{
	if (!lst)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_buf(t_buffer **lst, t_buffer *new)
{
	t_buffer	*ele;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
			return ;
		}
		else
		{
			ele = ft_lstlast_buf(*lst);
			ele->next = new;
		}
	}
}

void	ft_lstadd_back_op(t_operator **lst, t_operator *new)
{
	t_operator	*ele;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
			(*lst)->next = NULL;
			return ;
		}
		else
		{
			ele = ft_lstlast_op(*lst);
			ele->next = new;
		}
	}
}
