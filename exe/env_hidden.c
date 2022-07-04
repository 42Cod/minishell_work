/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_hidden.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:46:24 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/01 21:35:36 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_create_new_hidden(t_env2 **env_struct, char **env_array)
{
	t_env2	*new;
	int		i;

	i = 0;
	while (env_array && env_array[i])
	{
		new = ft_calloc(1, sizeof(t_env2));
		new->name_hidden = ft_substr(env_array[i], 0, env_break2(env_array[i]));
		new->value_hidden = ft_substr(env_array[i],
				env_break2(env_array[i]) + 1,
				ft_strlen(env_array[i]) - env_break2(env_array[i]) + 1);
		new->hidden = false;
		new->next = NULL;
		ft_lstadd_back_env_hd(env_struct, new);
		i++;
	}
	return (0);
}

int	env_break2(char *env_array)
{	
	int	i;

	i = 0;
	while (env_array[i])
	{
		if (env_array[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	env_start2(char *env_array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_array[i] != '=')
	{
		i++;
		j++;
	}
	i = 0;
	while (env_array[i])
		i++;
	return (i - j);
}

t_env2	*ft_lstlast_env2(t_env2 *lst)
{
	if (!lst)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env_hd(t_env2 **lst, t_env2 *new)
{
	t_env2	*ele;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
			return ;
		}
		else
		{
			ele = ft_lstlast_env2(*lst);
			ele->next = new;
		}
	}
}
