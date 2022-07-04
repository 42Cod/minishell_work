/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:07:09 by nmichael          #+#    #+#             */
/*   Updated: 2022/07/01 14:44:14 by marius           ###   ########.fr       */
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

static char	*get_env_value(char *cmd)
{
	char	*env_value;
	int		env_length;
	char	*cmd_at_equals;
	int		i;

	cmd_at_equals = ft_strrchr(cmd, '=') + 1;
	if (cmd_at_equals == NULL)
		return (NULL);
	env_length = ft_strlen(cmd_at_equals);
	env_value = ft_calloc(env_length, sizeof(*env_value));
	if (env_value == NULL)
		return (NULL);
	i = 0;
	while (i < env_length)
	{
		env_value[i] = cmd_at_equals[i];
		++i;
	}
	return (env_value);
}

static char	*get_env_name(char *cmd)
{
	char	*env_name;

	env_name = ft_substr(cmd, 0, ft_strrchr(cmd, '=') - cmd);
	if (env_name == NULL)
		return (NULL);
	return (env_name);
}

static bool	is_already_in_env(char *cmd, t_env2 *hidden_env)
{
	t_env2	*hidden_env_tmp;
	char	*env_name;
	int		length;

	env_name = get_env_name(cmd);
	hidden_env_tmp = hidden_env;
	while (hidden_env_tmp)
	{
		if (ft_strlen(hidden_env_tmp->name_hidden) > ft_strlen(env_name))
			length = ft_strlen(hidden_env_tmp->name_hidden);
		else
			length = ft_strlen(env_name);
		if (ft_strncmp(hidden_env_tmp->name_hidden, env_name,
				length) == 0)
		{
			free(env_name);
			return (true);
		}
		hidden_env_tmp = hidden_env_tmp->next;
	}
	free(env_name);
	return (false);
}

static void	overwrite_value(char *cmd, t_env *env, t_env2 *hidden_env)
{
	t_env	*tmp_env;
	t_env2	*tmp_hidden_env;
	char	*env_name;
	char	*env_value;

	env_name = get_env_name(cmd);
	env_value = get_env_value(cmd);
	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->name, env_name, ft_strlen(env_name)) == 0)
		{
			free(tmp_env->value);
			tmp_env->value = ft_strjoin("=", env_value);
			break ;
		}
		tmp_env = tmp_env->next;
	}
	tmp_hidden_env = hidden_env;
	while (tmp_hidden_env)
	{
		if (ft_strncmp(tmp_hidden_env->name_hidden, env_name, \
			ft_strlen(env_name)) == 0)
		{
			free(tmp_hidden_env->value_hidden);
			tmp_hidden_env->value_hidden = ft_strdup(env_value);
			break ;
		}
		tmp_hidden_env = tmp_hidden_env->next;
	}
	free(env_name);
	free(env_value);
}

int	ft_export(t_env *env, t_env2 *env2, t_input **input)
{
	int	error_env;
	int	i;
	int	flag;

	error_env = 0;
	flag = 0;
	if (!(*input)->cmd[1])
	{
		print4(env2);
		return (SUCCESS);
	}
	i = 0;
	while ((*input)->cmd[++i])
	{
		if (is_already_in_env((*input)->cmd[i], env2))
		{
			overwrite_value((*input)->cmd[i], env, env2);
			flag = 1;
		}
		error_env = is_valid_env((*input)->cmd[i]);
		if (error_env <= 0)
			return (print_error(error_env, (*input)->cmd[i]));
		if (error_env == 1 && flag == 0)
		{
			env_add(&env, (*input)->cmd[i]);
			env_add_hidden_2(&env2, (*input)->cmd[i]);
		}
		if (error_env == 2 && flag == 0)
			env_add_hidden_3(&env2, (*input)->cmd[i]);
		flag = 0;
	}
	return (SUCCESS);
}
