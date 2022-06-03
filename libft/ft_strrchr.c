/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 11:47:53 by nkolle            #+#    #+#             */
/*   Updated: 2021/08/13 15:03:14 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*pointer;
	int		i;

	i = 0;
	pointer = (char *)s;
	while (pointer[i] != '\0')
	{
		i++;
		s++;
	}
	while (&pointer[i] >= &pointer[0])
	{
		if (pointer[i] == (char)c)
			return (pointer + i);
		if (i == 0)
			return (NULL);
		if (pointer[i] != (char)c)
		{
			i--;
			s--;
		}
	}
	return (NULL);
}
