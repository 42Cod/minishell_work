/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 10:53:22 by nkolle            #+#    #+#             */
/*   Updated: 2021/08/06 14:20:28 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	h;
	size_t	needle_len;
	char	*ptr;

	i = 0;
	h = 0;
	needle_len = ft_strlen(needle);
	ptr = (char *)haystack;
	if (needle[0] == '\0')
		return (ptr);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + h] == needle[h]
			&& needle[h] != '\0' && (i + h) < len)
		{
			h++;
			if (h == needle_len)
				return (&ptr[i]);
		}
		i++;
		h = 0;
	}
	return (0);
}
