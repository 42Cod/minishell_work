/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:46:56 by nkolle            #+#    #+#             */
/*   Updated: 2022/06/03 13:57:10 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_exec_path(t_input	**input)
{
	char	*path;
	char	*path1;
	char	**split_path;
	int		i;

	i = -1;
	path = NULL;
	path1 = NULL;
	split_path = NULL;
	if (has_slash(input))
		return ((*input)->cmd[0]);
	path = find_path(input);
	if (path)
	{
		split_path = ft_split(path, ':');
		while (split_path[++i] != NULL)
		{
			path = ft_strjoin(split_path[i], "/\0");
			path1 = ft_strjoin(path, (*input)->cmd[0]);
			if (access(path1, X_OK) == 0)
				return (path1);
		}
	}
	write(1, "cmd not found\n", 14);
	return (NULL);
}

char	*find_path(t_input **input)
{
	t_env	*tmp_head;
	char	*ret;

	tmp_head = (*(*input)->env);
	while ((*(*input)->env) && (*(*input)->env)->name)
	{
		if (ft_strcmp((*(*input)->env)->name, "PATH") == 0)
		{
			ret = (*(*input)->env)->value;
			(*(*input)->env) = tmp_head;
			return (ret);
		}
		(*(*input)->env) = (*(*input)->env)->next;
	}
	(*(*input)->env) = tmp_head;
	return (NULL);
}

int	has_slash(t_input **input)
{
	int	i;

	i = 0;
	while ((*input)->cmd[0][i])
	{
		if ((*input)->cmd[0][i] == '/')
			return (1);
		i++;
	}
	return (0);
}
