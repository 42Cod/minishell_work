/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 10:50:51 by nkolle            #+#    #+#             */
/*   Updated: 2021/08/13 11:48:52 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*ptr;
	unsigned char		*target;

	i = 0;
	ptr = (unsigned char *)src;
	target = (unsigned char *)dst;
	if (ptr == NULL && target == NULL)
		return (NULL);
	if (ptr < target)
	{
		while (len-- > 0)
			target[len] = ptr[len];
	}
	else
	{
		while (i < len)
		{
			target[i] = ptr[i];
			i++;
		}
	}
	return (dst);
}
