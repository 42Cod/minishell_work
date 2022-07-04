/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:48:54 by nmichael          #+#    #+#             */
/*   Updated: 2022/07/04 19:58:03 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	executer_b(t_exe_locals *locals)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(locals->fd_standard_out, STDOUT_FILENO);
	dup2(locals->fd_standard_in, STDIN_FILENO);
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
	int	ret;

	g_state[0] = EXEC;
	init_locals(&locals);
	locals.pa = process_count(input, &locals.j);
	ret = 0;
	close (STDIN_FILENO);
	dup2(locals.fd_standard_in, STDIN_FILENO);
	while (locals.i < locals.j)
	{
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
	// safe_fd_set(&locals->fd_next, STDIN_FILENO);
	abs_cmd_path = find_exec_path(&input);
	if (abs_cmd_path == NULL || access(abs_cmd_path, F_OK) != 0)
	{
		exit(127);
	}
	exit_status = execve(abs_cmd_path, input->cmd, char_converter(&input));
	exit(exit_status);
	return (exit_status);
}
