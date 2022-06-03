/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:07:04 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/03 04:31:52 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_input *input)
{
	if (ft_strcmp(input->cmd[0], "exit") == 0 && !input->cmd[1])
	{
		ft_putendl_fd("exit", STDERR);
		input->ret = 0;
		exit(0);
	}
	if (ft_strisnum((input->cmd[1])) && !input->cmd[2])
	{
		ft_putendl_fd("exit", STDERR);
		input->ret = ft_atoi(input->cmd[1]);
		exit(0);
	}
	if (ft_strisnum((input->cmd[1])) && input->cmd[2])
	{
		ft_putendl_fd("exit", STDERR);
		ft_putendl_fd("\xf0\x9f\xa6\xa6: exit: too many arguments", STDERR);
		return ;
	}
	if (!ft_strisnum((input->cmd[1])))
	{
		ft_exit2(input);
	}
}

void	ft_exit2(t_input *input)
{
	ft_putendl_fd("exit", STDERR);
	ft_putendl_fd2("\xf0\x9f\xa6\xa6: exit: ", STDERR);
	ft_putstr_fd(input->cmd[1], STDERR);
	ft_putendl_fd(": numeric argument required", STDERR);
	exit(0);
}
