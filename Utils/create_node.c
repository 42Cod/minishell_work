/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:10:03 by nkolle            #+#    #+#             */
/*   Updated: 2022/07/26 17:22:36 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_buffer	*new_element(char *content)
{
	t_buffer	*new_element;

	new_element = NULL;
	new_element = ft_calloc(1, sizeof(t_buffer));
	if (new_element != NULL)
	{
		new_element->content = content;
		new_element->next = NULL;
	}
	return (new_element);
}

t_operator	*new_element_op(char *content, enum e_operator type)
{
	t_operator	*new_element;

	new_element = NULL;
	new_element = ft_calloc(1, sizeof(t_operator));
	if (new_element != NULL)
	{
		new_element->content = content;
		new_element->flag = 0;
		if (type == HEREDOC)
			new_element->redir_type = HEREDOC;
		if (type == OUT_APPEND)
			new_element->redir_type = OUT_APPEND;
		if (type == INFILE)
			new_element->redir_type = INFILE;
		if (type == OUT_TRUNCATE)
			new_element->redir_type = OUT_TRUNCATE;
		new_element->next = NULL;
	}
	return (new_element);
}
