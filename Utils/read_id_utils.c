/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_id_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:37:38 by nkolle            #+#    #+#             */
/*   Updated: 2022/06/02 19:40:10 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

t_buffer	*stringbuffer_create_node(t_buffer **buffer)
{
	t_buffer	*new_element_buf;

	(void)buffer;
	new_element_buf = malloc(sizeof(t_buffer));
	if (!new_element_buf)
		return (NULL);
	new_element_buf->content = NULL;
	new_element_buf->next = NULL;
	return (new_element_buf);
}

void	stringbuffer_destroy(t_buffer **buffer)
{
	free(*buffer);
	(*buffer) = NULL;
}

void	stringbuffer_get_string(t_buffer **buffer, char **str)
{
	*str = ft_strdup((*buffer)->content);
}

char	*sb_finalize(t_sb *sb)
{
	char			*str;
	unsigned int	i;

	str = malloc((sb->fill + 1) * sizeof(char));
	if (str != NULL)
	{
		i = 0;
		while (i < sb->fill)
		{
			str[i] = sb->buffer[i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
