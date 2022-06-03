/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 13:25:06 by nkolle            #+#    #+#             */
/*   Updated: 2022/05/27 15:57:27 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(*ptr) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	while (*s1 != '\0')
		ptr[i++] = *s1++;
	while (*s2 != '\0')
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	if (s1)
		free ((void *)s1);
	if (s2)
		free ((void *)s2);
	s1 = NULL;
	s2 = NULL;
	return (ptr);
}
