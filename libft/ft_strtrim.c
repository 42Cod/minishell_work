/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 16:59:08 by nkolle            #+#    #+#             */
/*   Updated: 2021/08/13 12:02:36 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		trimmedstrl;
	char		*trimmedstr;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr((char *)set, *s1))
		s1++;
	trimmedstrl = ft_strlen(s1);
	while (trimmedstrl && ft_strchr((char *)set, s1[trimmedstrl]))
		trimmedstrl--;
	trimmedstr = ft_substr((char *) s1, 0, trimmedstrl + 1);
	return (trimmedstr);
}
