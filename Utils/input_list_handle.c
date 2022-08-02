/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:22:12 by nkolle            #+#    #+#             */
/*   Updated: 2022/08/01 16:27:55 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_input	*ft_lstlast_cmd(t_input *lst)
{
	if (!lst)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_cmd(t_input **lst, t_input *new)
{
	t_input	*ele;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
			return ;
		}
		else
		{
			ele = ft_lstlast_cmd(*lst);
			ele->next = new;
		}
	}
}

t_input	*new_element_cmd(int cmd_length)
{
	t_input	*new_element;

	new_element = NULL;
	new_element = ft_calloc(1, sizeof(t_input));
	new_element->cmd = ft_calloc((cmd_length + 1), sizeof(char *));
	if (new_element != NULL)
		new_element->next = NULL;
	return (new_element);
}

void	create_new_input(t_input **input, int cmd_length, t_env **env,
t_operator **operator)
{
	t_input	*new_input;

	new_input = NULL;
	new_input = new_element_cmd(cmd_length);
	new_input->env = env;
	new_input->operator = *operator;
	ft_lstadd_back_cmd(input, new_input);
}

void	append_linked_list_to_input(t_input **input, t_operator **operator,
	t_buffer **buffer, t_env **env)
{
	int			cmd_length;
	t_buffer	*tmp;

	tmp = (*buffer);
	cmd_length = 0;
	while (tmp != NULL)
	{
		cmd_length++;
		tmp = tmp->next;
	}
	create_new_input(input, cmd_length, env, operator);
	add_buffer_cmd(buffer, input);
	if ((*operator) != NULL)
		(*input)->operator = (*operator);
}
