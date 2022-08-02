/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:48:54 by nmichael          #+#    #+#             */
/*   Updated: 2022/08/02 11:55:10 by marius           ###   ########.fr       */
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

	init_locals(&locals);
	locals.pa = process_count(input, &locals.j);
	close (STDIN_FILENO);
	dup2(locals.fd_standard_in, STDIN_FILENO);
	if (exec_redir(input, &locals, 0) == 1)
		return (0);
	while (locals.i < locals.j)
	{
		printf("TEST\n");
		if (g_state[2] != BREAK)
			check_for_dollar(input, env2);
		locals.exit_status = executer_a(input, env2, &locals);
		locals.i++;
		input = input->next;
	}
	g_state[2] = START;
	executer_b(&locals);

	return (WEXITSTATUS(locals.exit_status));
}

int	child_proc(t_input *input, t_exe_locals *locals, t_env2 *env2)
{
	char	*abs_cmd_path;
	int		exit_status;

	(void)env2;
	(void)locals;
	abs_cmd_path = find_exec_path(&input);
	if (abs_cmd_path == NULL || access(abs_cmd_path, F_OK) != 0)
	{
		exit(127);
	}
	if (is_builtin((*(*input).cmd)))
	{
		exit_status = exec_builtin(&input, *(input->env),
		env2, char_converter(&input));
	}
	else
		exit_status = execve(abs_cmd_path, input->cmd, char_converter(&input));
	exit(exit_status);
	return (exit_status);
}
