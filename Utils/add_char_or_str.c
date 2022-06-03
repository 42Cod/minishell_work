/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char_or_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:46:55 by nkolle            #+#    #+#             */
/*   Updated: 2022/05/24 15:33:32 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	stringbuffer_append_char(t_buffer **buffer, char c)
{
	char	*newstr;
	int		count;

	newstr = NULL;
	newstr = ft_calloc(ft_strlen((*buffer)->content) + 2, sizeof(char));
	if (!newstr)
		return (0);
	count = 0;
	while ((*buffer)->content != NULL && (*buffer)->content[count] != '\0')
	{
		newstr[count] = (*buffer)->content[count];
		count++;
	}
	newstr[count] = c;
	newstr[count + 1] = '\0';
	if ((*buffer)->content != NULL)
		free((*buffer)->content);
	(*buffer)->content = newstr;
	return (1);
}

void	append_string_to_linked_list(t_buffer **buffer, char *content)
{
	t_buffer	*new_buffer;

	new_buffer = NULL;
	new_buffer = new_element(content);
	ft_lstadd_back_buf(buffer, new_buffer);
}

void	append_string_to_redirection_list(t_operator **operator,
	enum e_operator type, char *content)
{
	t_operator	*new_op;

	new_op = NULL;
	new_op = new_element_op(content, type);
	new_op->flag = 0;
	ft_lstadd_back_op(operator, new_op);
}
