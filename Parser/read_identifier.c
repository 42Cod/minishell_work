/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_identifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:34:55 by nmichael          #+#    #+#             */
/*   Updated: 2022/08/01 13:25:48 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_identifier(char **line_comb)
{
	char		*str;
	t_buffer	*buffer;

	buffer = NULL;
	str = NULL;
	buffer = ft_calloc(1, sizeof(t_buffer));
	stringbuffer_create_node(&buffer);
	rd_helper(line_comb, &buffer);
	stringbuffer_get_string(&buffer, &str);
	stringbuffer_destroy(&buffer);
	return (str);
}

void	rd_helper(char **line_comb, t_buffer **buffer)
{
	while (**line_comb)
	{
		if (**line_comb == '\'')
		{
			(*line_comb)++;
			// if (((**line_comb)) == '$')
			// {
			// 	rd_dollar(line_comb, buffer);
			// 	break ;
			// }
			read_single_quoted(line_comb, buffer);
			(*line_comb)++;
			break ;
		}
		else if (**line_comb == '"')
		{
			helper_3(buffer, line_comb);
			break ;
		}
		else if (is_breaking_char(line_comb) == 1)
			break ;
		else
			helper_2(buffer, line_comb);
	}
}

void	helper_2(t_buffer **buffer, char **line_comb)
{
	stringbuffer_append_char(buffer, **line_comb);
	(*line_comb)++;
}

void	helper_3(t_buffer **buffer, char **line_comb)
{
	(*line_comb)++;
	read_double_quoted(line_comb, buffer);
	(*line_comb)++;
}

void	helper_4(t_input **input,
	t_operator **operator, t_buffer **buffer, t_env **env)
{
	append_linked_list_to_input(input, operator, buffer, env);
	operator = NULL;
}
