/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:07:15 by nmichael          #+#    #+#             */
/*   Updated: 2022/07/01 14:43:32 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_size(char *env)
{
	int	i;

	i = 0;
	while (env && env[i] && env[i] != '=')
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
	env->value = ft_memdel(env->value);
	env->name = ft_memdel(env->name);
	env = ft_memdel(env);
}

void	free_node2(t_env2 *env2)
{
	env2->value_hidden = ft_memdel(env2->value_hidden);
	env2->name_hidden = ft_memdel(env2->name_hidden);
	env2 = ft_memdel(env2);
}

int	ft_unset(t_env *env, t_env2 *env2, t_env2 *prev, t_input **input)
{
	t_env	*tmp;
	t_env2	*tmp2;

	if ((*input)->cmd[1] == NULL)
		return(1);
	if (ft_strncmp((*input)->cmd[1], env->name,
				env_size(env->name)) == 0)
	{
		tmp = env->next;
		free_node(env);
		env->next = tmp;
	}
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
	if (ft_strncmp((*input)->cmd[1], env2->name_hidden,
				env_size(env2->name_hidden)) == 0)
	{
			tmp2 = env2->next;
			free_node2(env2);
			prev->next = tmp2;
			env2 = prev;
	}
	while (env2 && env2->next)
	{
		if (ft_strncmp((*input)->cmd[1], env2->next->name_hidden,
				env_size(env2->next->name_hidden)) == 0)
			helper6(env2, tmp2);
		env2 = env2->next;
	}
	return (SUCCESS);
}
