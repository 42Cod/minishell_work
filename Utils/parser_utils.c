/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:44:30 by nkolle            #+#    #+#             */
/*   Updated: 2022/06/02 20:35:48 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_whitespace(char **line_comb)
{
	while (**line_comb == (int)32 || **line_comb == (int)9)
		(*line_comb)++;
}

int	check_for_str(char *s, char *str)
{
	while (1)
	{
		if (*str == '\0')
			return (1);
		if (*s != *str)
			return (0);
		str++;
		s++;
	}
}

int	check_for_c(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != (char)c)
	{
		if ((char)c == '\0' && *str == '\0')
			return (1);
		if (*str == '\0' && (char)c != '\0')
			return (0);
		str++;
	}
	return (0);
}

void	create_op_files(t_operator **operator)
{
	t_operator	*tmp;
	int			trash_fd;

	tmp = (*operator);
	while (tmp != NULL)
	{
		if (tmp->content == NULL)
		{
			tmp = tmp->next;
			continue ;
		}
		trash_fd = open(tmp->content, O_CREAT, 0777);
		close(trash_fd);
		tmp = tmp->next;
	}
	(*operator)->flag = 1;
}
