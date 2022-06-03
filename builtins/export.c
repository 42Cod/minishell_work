/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:07:09 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/03 04:32:22 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(int error, char *arg)
{
	int	i;

	if (error == -1)
		ft_putstr_fd ("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd ("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write (STDERR, &arg[i], 1);
		i++;
	}
	write (STDERR, "\n", 1);
	return (ERROR);
}

int	is_valid_env(char *envp)
{
	int	i;

	i = 0;
	if (ft_isdigit(envp[i]) == 1)
		return (0);
	if (!envp[2])
		return (3);
	while (envp[i] && envp[i] != '=')
	{
		if (ft_isalnum(envp[i]) == 0)
			return (-1);
		i++;
	}
	if (envp[i] != '=')
		return (2);
	return (1);
}

int	env_add(t_env **env_struct, char *cmd)
{
	t_env	*new;
	int		i;

	i = 0;
	new = ft_calloc(1, sizeof(t_env));
	new->name = ft_substr(&cmd[i], 0, env_break(&cmd[i]));
	new->value = ft_substr(&cmd[i], env_break(&cmd[i]),
			env_start(&cmd[i]));
	new->hidden = false;
	new->next = NULL;
	ft_lstadd_back_env(env_struct, new);
	i++;
	return (0);
}

int	ft_export(t_env *env, t_env2 *env2, t_input **input)
{
	int	error_env;
	int	i;

	error_env = 0;
	if (!(*input)->cmd[1])
	{
		print4(env2);
		return (SUCCESS);
	}
	i = 1;
	while ((*input)->cmd[i])
	{
		error_env = is_valid_env((*input)->cmd[i]);
		if (error_env <= 0)
			return (print_error(error_env, (*input)->cmd[i]));
		if (error_env == 1)
		{
			env_add(&env, (*input)->cmd[i]);
			env_add_hidden_2(&env2, (*input)->cmd[i]);
		}
		else
			env_add_hidden_3(&env2, (*input)->cmd[i]);
		i++;
	}
	return (SUCCESS);
}
