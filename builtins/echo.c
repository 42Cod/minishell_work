/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:45:03 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/03 13:00:41 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	new = malloc(sizeof(char) * (i + j + 1));
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

int	ft_echo(t_input **input)
{
	int		i;
	int		newline;

	i = 1;
	newline = 0;
	if (input)
	{
		while ((*input)->cmd[i] && ft_strcmp((*input)->cmd[i], "-n") == 0)
		{
			newline = 1;
			i++;
		}
		while ((*input)->cmd[i])
		{
			if (check_nip(input) == 1)
				break ;
			ft_putstr_fd((*input)->cmd[i], 1);
			if ((*input)->cmd[i + 1] && (*input)->cmd[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (newline == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}

int	check_nip(t_input **input)
{
	if (ft_strchr((*input)->cmd[1], '\'') == 0)
		return (0);
	if (ft_strchr((*input)->cmd[1], '\'') == 1)
	{
		create_new_putstr(input);
		return (1);
	}
	return (0);
}

char	*create_new_putstr(t_input **input)
{
	char	*ret;

	ret = ft_substr((*input)->cmd[1], 1, (ft_strlen((*input)->cmd[1]) - 2));
	ft_putstr_fd(ret, 1);
	return (ret);
}
