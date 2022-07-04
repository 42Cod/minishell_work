/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:48:54 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/03 13:58:11 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	executer_b(t_exe_locals *locals)
{
	safe_fd_set(&locals->fd_in, STDIN_FILENO);
	safe_fd_set(&locals->fd_out, STDOUT_FILENO);
	safe_fd_set(&locals->fd_next, STDIN_FILENO);
	locals->i = 0;
	while (locals->i < locals->j)
	{
		waitpid(locals->pa[locals->i], &locals->exit_status, 0);
		locals->i++;
	}
}

int	executer(t_input *input, t_env2 *env2)
{
	t_exe_locals	locals;	

	g_state[0] = EXEC;
	init_locals(&locals);
	locals.pa = process_count(input, &locals.j);
	while (locals.i < locals.j)
	{
		safe_fd_set(&locals.fd_in, locals.fd_next);
		if (locals.i == locals.j - 1)
			safe_fd_set(&locals.fd_out, STDOUT_FILENO);
		else
		{
			if (!safe_pipe(&locals.fd_out, &locals.fd_next))
				return (2);
		}
		check_for_dollar(input, env2);
		locals.exit_status = executer_a(input, env2, &locals);
		locals.i++;
		input = input->next;
	}
	executer_b(&locals);
	return (WEXITSTATUS(locals.exit_status));
}

int	child_proc(t_input *input, t_exe_locals *locals, t_env2 *env2)
{
	char	*abs_cmd_path;
	int		exit_status;

	(void)env2;
	dup2(locals->fd_in, STDIN_FILENO);
	dup2(locals->fd_out, STDOUT_FILENO);
	safe_fd_set(&locals->fd_in, STDIN_FILENO);
	safe_fd_set(&locals->fd_out, STDOUT_FILENO);
	safe_fd_set(&locals->fd_next, STDIN_FILENO);
	abs_cmd_path = find_exec_path(&input);
	if (abs_cmd_path == NULL || access(abs_cmd_path, F_OK) != 0)
	{
		exit(127);
	}
	exit_status = execve(abs_cmd_path, input->cmd, char_converter(&input));
	exit(exit_status);
	return (exit_status);
}
