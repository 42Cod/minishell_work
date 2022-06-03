/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_proto.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:13:10 by nkolle            #+#    #+#             */
/*   Updated: 2022/06/03 13:57:53 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*process_count(t_input *input, int *j)
{
	t_input	*tmp;
	int		*process_array;

	*j = 0;
	tmp = input;
	while (tmp != NULL)
	{
		(*j)++;
		tmp = tmp->next;
	}
	process_array = ft_calloc((*j), sizeof(int));
	return (process_array);
}

int	safe_fd_set(int *loc, int value)
{
	if (*loc != value)
	{
		if (value < 0)
			return (0);
		if (*loc != STDIN_FILENO && *loc != STDOUT_FILENO)
		{
			close(*loc);
		}
		*loc = value;
	}
	return (1);
}

int	safe_pipe(int *left, int *right)
{
	int	fds[2];

	if (pipe(fds) != 0)
		return (0);
	safe_fd_set(left, fds[1]);
	safe_fd_set(right, fds[0]);
	return (1);
}

void	executer_a(t_input *input, t_env2 *env2, t_exe_locals	*locals)
{
	if (exec_redir(input, locals) == 0)
	{
		if (is_builtin((*(*input).cmd)))
		{
			dup2(locals->fd_out, STDOUT_FILENO);
			g_state[1] = exec_builtin(&input, *(input->env),
					env2, char_converter(&input));
			dup2(locals->fd_standard_out, STDOUT_FILENO);
		}
		else
		{
			locals->pid = fork();
			if (locals->pid < 0)
			{
				write(1, "ERRORPIPE", 10);
				return ;
			}
			if (locals->pid == 0)
				child_proc(input, locals, env2);
		}
	}
}
