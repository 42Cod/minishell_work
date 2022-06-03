/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:29:57 by nkolle            #+#    #+#             */
/*   Updated: 2022/05/30 18:42:59 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_chars(const char *str, char *new, char find)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != find)
			new[i] = str[i];
		else if (str[i] == find)
			new[i] = '\0';
		i++;
	}
	new[i] = '\0';
	return (new);
}

static size_t	ft_wordcount(char *newstr, size_t len)
{
	size_t	i;
	size_t	repl;

	i = 0;
	repl = 0;
	while (i < len)
	{
		if (newstr[i] == '\0' && newstr[i + 1] != newstr[i])
			repl++;
		i++;
	}
	i = 0;
	while (newstr[i] != '\0')
	{
		if (newstr[len] == '\0')
			return (repl + 1);
		i++;
	}
	return (repl);
}

static char	**ft_strsav(char **ptr, char *newstr, size_t count, size_t len_s)
{
	size_t	len;
	size_t	arrays;

	arrays = 0;
	len = 0;
	newstr[len_s] = '\0';
	while (newstr[len] == '\0' && arrays < count)
		len++;
	while (arrays < count)
	{
		ptr[arrays] = ft_strdup(&newstr[len]);
		if (ptr[arrays] == NULL)
		{
			free(ptr);
			free(newstr);
			return (NULL);
		}
		len += ft_strlen(&newstr[len]);
		arrays++;
		while (newstr[len] == '\0' && arrays < count)
			len++;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	*newstr;
	char	**end_pointer;
	size_t	count;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	newstr = (char *) malloc(sizeof(char) * (len + 1));
	if (newstr == NULL)
		return (NULL);
	ft_chars(s, newstr, c);
	count = ft_wordcount(newstr, len);
	end_pointer = malloc(sizeof(char *) * (count + 1));
	if (end_pointer == NULL)
	{
		free(newstr);
		return (NULL);
	}
	ft_strsav(end_pointer, newstr, count, len);
	end_pointer[count] = NULL;
	free(newstr);
	return (end_pointer);
}
