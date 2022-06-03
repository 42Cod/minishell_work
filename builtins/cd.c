/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:13:30 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/03 04:03:06 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(t_input **input)
{
	ft_putstr_fd("cd: ", 2);
	if ((*input)->cmd[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd((*input)->cmd[1], 2);
}

char	*get_path(t_env *env, char *var, int len)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			oldpwd = malloc(sizeof(char) * s_alloc + 1);
			i = 0;
			j = 0;
			while (env->value[i++])
			{
				if (i > (int)len)
					oldpwd[j++] = env->value[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

int	oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	env_add(&env, oldpwd);
	ft_memdel(oldpwd);
	return (SUCCESS);
}

int	to_path(int value, t_env *env)
{
	int		ret;
	char	*path;

	if (value == 0)
	{
		oldpwd(env);
		path = getenv("HOME");
		if (!path)
			ft_putendl_fd("minishell : cdv : HOME not set", STDERR);
		if (!path)
			return (ERROR);
	}
	if (value == 1)
	{
		path = get_path(env, "OLDPWD", 6);
		if (!path)
			ft_putendl_fd("minishell : cdv : OLDPWD not set", STDERR);
		if (!path)
			return (ERROR);
		oldpwd(env);
	}
	ret = chdir(path);
	return (ret);
}

int	ft_cd(t_input **input, t_env *env)
{
	int	ret;

	if (!(*input)->cmd[1])
		return (to_path(0, env));
	if (ft_strcmp((*input)->cmd[1], "-") == 0)
		ret = to_path(1, env);
	else
	{
		oldpwd(env);
		ret = chdir((*input)->cmd[1]);
		if (ret < 0)
			ret *= -1;
		if (ret != 0)
			ft_error(input);
	}
	return (ret);
}
