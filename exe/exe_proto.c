/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_proto.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:13:10 by nkolle            #+#    #+#             */
/*   Updated: 2022/07/26 17:17:53 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_child_fds(t_exe_locals *locals, int fd[2])
{
	if (locals->fd_in != STDIN_FILENO)
	{
		dup2(locals->fd_in, STDIN_FILENO);
		close(locals->fd_in);
	}
	if (locals->fd_out != STDOUT_FILENO)
		dup2(locals->fd_out, STDOUT_FILENO);
	else if (locals->i != locals->j - 1)
		dup2(fd[1], STDOUT_FILENO);
	else if (locals->i == locals->j - 1)
	{
		close(STDOUT_FILENO);
		dup2(locals->fd_standard_out, STDOUT_FILENO);
	}
	protected_close(locals->fd_out);
	close(fd[0]);
	close(fd[1]);
}

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

int	executer_a(t_input *input, t_env2 *env2, t_exe_locals	*locals)
{
	int	exit_status;
	int	fd[2];

	exit_status = 0;
	pipe(fd);
	if (1)
	{
		if (is_builtin((*(*input).cmd)))
		{
			dup2(locals->fd_out, STDOUT_FILENO);
			exit_status = exec_builtin(&input, *(input->env),
					env2, char_converter(&input));
			dup2(locals->fd_standard_out, STDOUT_FILENO);
		}
		else
		{
			locals->pid = fork();
			if (locals->pid < 0)
			{
				write(1, "ERRORPIPE", 10);
				return (-1);
			}
			if (locals->pid == 0)
			{
				handle_child_fds(locals, fd);
				exec_redir(input, locals, 1);
				exit_status = child_proc(input, locals, env2);
			}
			else if (locals->pid != 0)
			{
				locals->pa[locals->i] = locals->pid;
				close(fd[1]);
				protected_close(locals->fd_in);
				protected_close(locals->fd_out);
				if (locals->i != locals->j - 1 && locals->fd_next == 0)
					locals->fd_in = dup(fd[0]);
				close(fd[0]);
			}
		}
	}
	return (exit_status);
}
