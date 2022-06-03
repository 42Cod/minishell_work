/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:00:37 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/03 05:13:26 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print4(t_env2 *input)
{
	while (input)
	{
		printf("declare -x %s", input->name_hidden);
		if ((input->value_hidden))
		{
			printf("=\"%s", input->value_hidden);
			printf("\"");
			printf("\n");
		}
		else
			printf("\n");
		input = input->next;
	}
}

void	print5(t_env *input)
{
	while (input)
	{
		printf("%s", input->name);
		printf("%s\n", input->value);
		input = input->next;
	}
}

void	helper6(t_env2 *env2, t_env2 *tmp2)
{
	tmp2 = env2->next->next;
	free_node2(env2->next);
	env2->next = tmp2;
}
