/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list_to_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:06:02 by nkolle            #+#    #+#             */
/*   Updated: 2022/05/24 15:31:58 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_buffer_cmd(t_buffer **buffer, t_input **input)
{
	t_buffer	*tmp;
	t_input		*tmp2;
	int			i;

	i = 0;
	tmp2 = ft_lstlast_cmd(*input);
	while ((*buffer) != NULL)
	{
		tmp = (*buffer);
		tmp2->cmd[i] = ft_strdup((*buffer)->content);
		(*buffer) = (*buffer)->next;
		free(tmp);
		i++;
	}
	tmp2->cmd[i] = NULL;
}
