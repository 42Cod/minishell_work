/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 10:50:29 by nkolle            #+#    #+#             */
/*   Updated: 2021/08/09 14:55:33 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*target;

	i = 0;
	ptr = (unsigned char *)src;
	target = (unsigned char *)dst;
	if (dst == 0 && src == 0)
		return (0);
	while (i < n)
	{
		target[i] = ptr[i];
		i++;
	}
	return (dst);
}
