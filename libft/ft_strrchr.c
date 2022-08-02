/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 11:47:53 by nkolle            #+#    #+#             */
/*   Updated: 2022/08/01 14:03:02 by marius           ###   ########.fr       */
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
		{
			printf("instrchrr pointer %s\n", pointer);
			printf("instrchrr pointer+i %s\n", (pointer + i));
			return (pointer + i);
		}
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
