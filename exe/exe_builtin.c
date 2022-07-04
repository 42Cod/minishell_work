/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:56:18 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/30 17:13:04 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_builtin(char *cmd)
{
	if ((ft_strcmp(cmd, "echo") == 0)
		|| (ft_strcmp(cmd, "export") == 0)
		|| (ft_strcmp(cmd, "cd") == 0)
		|| (ft_strcmp(cmd, "pwd") == 0)
		|| (ft_strcmp(cmd, "env") == 0)
		|| (ft_strcmp(cmd, "unset") == 0)
		|| (ft_strcmp(cmd, "exit") == 0))
	{
		return (1);
	}
	return (0);
}

int	exec_builtin(t_input **input, t_env *env, t_env2 *env2, char **envp)
{
	int		res;

	res = 0;
	(void)envp;
	if (ft_strcmp((*input)->cmd[0], "echo") == 0)
		res = ft_echo(input);
	if (ft_strcmp((*input)->cmd[0], "export") == 0)
		ft_export(env, env2, input);
	if (ft_strcmp((*input)->cmd[0], "cd") == 0)
		res = ft_cd(input, env);
	if (ft_strcmp((*input)->cmd[0], "pwd") == 0)
		res = ft_pwd();
	if (ft_strcmp((*input)->cmd[0], "env") == 0)
		ft_env(env);
	if (ft_strcmp((*input)->cmd[0], "unset") == 0)
		ft_unset(env, env2, NULL, input); // NOT NULL!!! NULL should be previous
	if (ft_strcmp((*input)->cmd[0], "exit") == 0)
		ft_exit(*input);
	return (res);
}
