/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:09:47 by nkolle            #+#    #+#             */
/*   Updated: 2022/06/03 05:02:39 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_redir(t_input *input, t_exe_locals *locals)
{
	while (input->operator != NULL)
	{
		if (input->operator->redir_type == INFILE)
		{
			if (redirct_stdin(input, locals) == 0)
				return (1);
		}
		else if (input->operator->redir_type == HEREDOC)
		{
			if (redirct_std_type_in(input, locals) == 0)
				return (1);
		}
		else if (input->operator->redir_type == OUT_TRUNCATE)
		{
			if (redirct_trunc(input, locals) == 0)
				return (1);
		}
		else if (input->operator->redir_type == OUT_APPEND)
		{
			if (redirct_app(input, locals) == 0)
				return (1);
		}
		input->operator = input->operator->next;
	}
	return (0);
}

int	redirct_stdin(t_input *tmp, t_exe_locals *locals)
{
	int	fd;

	fd = open(tmp->operator->content, O_RDONLY, 0777);
	if (fd < 0)
		return (0);
	safe_fd_set(&locals->fd_in, fd);
	return (1);
}

int	redirct_std_type_in(t_input *tmp, t_exe_locals *locals)
{
	int	pipe_fd;

	pipe_fd = STDOUT_FILENO;
	safe_pipe(&pipe_fd, &locals->fd_in);
	write(pipe_fd, tmp->operator->content, strlen(tmp->operator->content));
	close(pipe_fd);
	return (1);
}

int	redirct_trunc(t_input *tmp, t_exe_locals *locals)
{
	if (locals->fd_out > 1)
		close(locals->fd_out);
	return (safe_fd_set(&locals->fd_out, open(
				tmp->operator->content,
				O_WRONLY | O_CREAT | O_RDONLY | O_TRUNC, 0777)));
}

int	redirct_app(t_input *tmp, t_exe_locals *locals)
{
	if (locals->fd_out > 1)
		close(locals->fd_out);
	return (safe_fd_set(&locals->fd_out, open(
				tmp->operator->content,
				O_APPEND | O_CREAT | O_WRONLY, 0777)));
}
