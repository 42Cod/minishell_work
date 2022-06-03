/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:38:05 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/03 02:45:42 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_single_quoted(char **line_comb, t_buffer **buffer)
{
	int	flag;

	flag = 0;
	while (**line_comb != '\'')
	{
		if (**line_comb == '\'')
			flag = 1;
		if (**line_comb == '\0' && flag == 0)
			exit(0);
		if (**line_comb == '\0' || flag == 1)
		{
			(*line_comb)++;
			break ;
		}
		stringbuffer_append_char(buffer, **line_comb);
		(*line_comb)++;
	}
}

void	read_double_quoted(char **line_comb, t_buffer **buffer)
{
	int	flag;

	flag = 0;
	while (**line_comb != '"')
	{
		if (**line_comb == '\"')
			flag = 1;
		if (**line_comb == '\0' && flag == 0)
			exit(0);
		if (**line_comb == '\0' || flag == 1)
		{
			(*line_comb)++;
			break ;
		}
		stringbuffer_append_char(buffer, **line_comb);
		(*line_comb)++;
	}
}

int	is_breaking_char(char **line_comb)
{
	if (**line_comb == '<' || **line_comb == '>'
		|| **line_comb == '|' || **line_comb == ' '
		|| **line_comb == (int)9 || **line_comb == '\n' || **line_comb == '\0')
		return (1);
	return (0);
}

void	fck_norm5(char **line_comb, t_buffer **buffer)
{
	skip_whitespace(line_comb);
	append_string_to_linked_list(buffer, read_identifier(line_comb));
}

void	rd_dollar(char **line_comb, t_buffer **buffer)
{
	int	flag;

	flag = 0;
	(*line_comb)--;
	while (**line_comb)
	{
		stringbuffer_append_char(buffer, **line_comb);
		(*line_comb)++;
		if (**line_comb == '\'')
			flag = 1;
		if (**line_comb == '\0' && flag == 0)
			exit(0);
		if (flag == 1)
		{
			stringbuffer_append_char(buffer, **line_comb);
			(*line_comb)++;
			break ;
		}
	}
}
