/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:56:18 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/02 23:11:57 by nkolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_create_new(t_env **env_struct, char **env_array)
{
	t_env	*new;
	int		i;

	i = 0;
	while (env_array && env_array[i])
	{
		new = ft_calloc(1, sizeof(t_env));
		new->name = ft_substr(env_array[i], 0, env_break(env_array[i]));
		new->value = ft_substr(env_array[i], env_break(env_array[i]),
				env_start(env_array[i]));
		new->hidden = false;
		new->next = NULL;
		ft_lstadd_back_env(env_struct, new);
		i++;
	}
	return (0);
}

int	env_break(char *env_array)
{	
	int	i;

	i = 0;
	while (env_array && env_array[i])
	{
		if (env_array[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	env_start(char *env_array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_array && env_array[i] != '=')
	{
		i++;
		j++;
	}
	i = 0;
	while (env_array && env_array[i])
		i++;
	return (i - j);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*ele;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
			return ;
		}
		else
		{
			ele = ft_lstlast_env(*lst);
			ele->next = new;
		}
	}
}
