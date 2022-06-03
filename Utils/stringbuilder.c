/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:14:16 by nkolle            #+#    #+#             */
/*   Updated: 2022/06/02 19:39:53 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sb_create(t_sb *sb)
{
	sb->buffer = malloc(128 * sizeof(char));
	sb->alloc = 128;
	sb->fill = 0;
}

void	sb_destroy(t_sb *sb)
{
	if (sb->buffer != NULL)
		free (sb->buffer);
}

void	sb_resize(t_sb *sb, unsigned int size)
{
	char			*new_buffer;
	unsigned int	i;

	new_buffer = malloc(size * sizeof(char));
	if (new_buffer != NULL)
	{
		if (sb->buffer != NULL)
		{
			i = 0;
			while (i < sb->fill)
			{
				new_buffer[i] = sb->buffer[i];
				i++;
			}
			free(sb->buffer);
		}
		sb->buffer = new_buffer;
	}
}

void	sb_append_char(t_sb *sb, char c)
{
	if (sb->fill >= sb->alloc)
		sb_resize(sb, sb->alloc * 2);
	sb->buffer[sb->fill] = c;
	sb->fill++;
}

void	sb_append_string(t_sb *sb, const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		sb_append_char(sb, str[i]);
		i++;
	}
}
