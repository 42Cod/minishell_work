/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:07:15 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/03 05:15:30 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_size(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	free_node(t_env *env)
{
	ft_memdel(env->value);
	ft_memdel(env->name);
	ft_memdel(env);
}

void	free_node2(t_env2 *env2)
{
	ft_memdel(env2->value_hidden);
	ft_memdel(env2->name_hidden);
	ft_memdel(env2);
}

int	ft_unset(t_env *env, t_env2 *env2, t_input **input)
{
	t_env	*tmp;
	t_env2	*tmp2;

	while (env && env->next)
	{
		if (ft_strncmp((*input)->cmd[1], env->next->name,
				env_size(env->next->name)) == 0)
		{
			tmp = env->next->next;
			free_node(env->next);
			env->next = tmp;
		}
		env = env->next;
	}
	tmp2 = NULL;
	while (env2 && env2->next)
	{
		if (ft_strncmp((*input)->cmd[1], env2->next->name_hidden,
				env_size(env2->next->name_hidden)) == 0)
		{
			helper6(env2, tmp2);
		}
		env2 = env2->next;
	}
	return (SUCCESS);
}
