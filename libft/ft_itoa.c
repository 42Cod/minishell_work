/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 17:16:57 by nkolle            #+#    #+#             */
/*   Updated: 2021/08/13 14:28:08 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_edge0(void)
{
	char	*res;

	res = (char *)malloc(2 * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

static char	*ft_negative_edge(void)
{
	char	*res;

	res = (char *)malloc(12 * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[0] = '-';
	res[1] = '2';
	res[2] = '1';
	res[3] = '4';
	res[4] = '7';
	res[5] = '4';
	res[6] = '8';
	res[7] = '3';
	res[8] = '6';
	res[9] = '4';
	res[10] = '8';
	res[11] = '\0';
	return (res);
}

static int	ft_lenn(int n)
{
	int	counter;

	counter = 0;
	if (n < 0)
	{
		counter++;
		n *= -1;
	}
	if (n == 0)
		counter++;
	while (n > 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len_n;
	int		i;

	i = 0;
	len_n = ft_lenn(n);
	if (n == 0)
		return (ft_edge0());
	if (n == -2147483648)
		return (ft_negative_edge());
	ptr = (char *)malloc((len_n + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		ptr[0] = '-';
	}
	ptr[len_n] = '\0';
	while (n > 0)
	{
		ptr[len_n - 1 - i++] = ((n % 10) + '0');
		n /= 10;
	}
	return (ptr);
}
