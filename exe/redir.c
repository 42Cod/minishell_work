/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:09:47 by nkolle            #+#    #+#             */
/*   Updated: 2022/08/01 17:47:59 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redirct_stdin(t_input *tmp, t_exe_locals *locals, int set);
static int	redirct_std_type_in(t_input *tmp, t_exe_locals *locals, int set);
static int	redirct_trunc(t_input *tmp, t_exe_locals *locals, int set);
static int	redirct_app(t_input *tmp, t_exe_locals *locals, int set);

int	exec_redir(t_input *input, t_exe_locals *locals, int set)
{
	t_input* head;

	head = input;
	
	while (input->operator != NULL)
	{
		printf("TYPE: %d\n", input->operator->redir_type);
		printf("ENUM TYPE: %d\n", HEREDOC);
		if (input->operator->redir_type == INFILE)
		{
			if (redirct_stdin(input, locals, set) == 0)
				return (1);
		}
		else if (input->operator->redir_type == HEREDOC)
		{
			printf("heredoc found\n");
			printf("set: %d\n", set);
			if (redirct_std_type_in(input, locals, set) == 0)
				return (1);
		}
		else if (input->operator->redir_type == OUT_TRUNCATE)
		{
			if (redirct_trunc(input, locals, set) == 0)
				return (1);
		}
		else if (input->operator->redir_type == OUT_APPEND)
		{
			if (redirct_app(input, locals, set) == 0)
				return (1);
		}
		input->operator = input->operator->next;
	}
	input = head;
	return (0);
}

static int	redirct_stdin(t_input *tmp, t_exe_locals *locals, int set)
{
	int	fd;

	fd = 0;
	if (set == 0)
	{
		locals->fd_in = open(tmp->operator->content, O_RDONLY, 0777);
		fd = locals->fd_in;
		if (locals->fd_in < 0)
			return (0);
	}
	else if (set == 1)
	{
		locals->fd_in = open(tmp->operator->content, O_WRONLY, 0777);
		safe_fd_set(&locals->fd_in, fd);
	}
	return (1);
}

static int	redirct_std_type_in(t_input *tmp, t_exe_locals *locals, int set)
{
	int	pipe_fd;

	// if (set == 1)
	// {
		(void)set;
		pipe_fd = STDOUT_FILENO;
		safe_pipe(&pipe_fd, &locals->fd_in);
		write(pipe_fd, tmp->operator->content, strlen(tmp->operator->content));
		close(pipe_fd);
	// }
	return (1);
}

static int	redirct_trunc(t_input *tmp, t_exe_locals *locals, int set)
{
	if (set == 0)
		locals->fd_out = open(tmp->operator->content,
			O_WRONLY | O_CREAT | O_RDONLY | O_TRUNC, 0777);
	else if (set == 1)
	{
		if (locals->fd_out > 1)
			close(locals->fd_out);
		return (safe_fd_set(&locals->fd_out, open(
					tmp->operator->content,
					O_WRONLY, 0777)));
	}
	return (1);
}

static int	redirct_app(t_input *tmp, t_exe_locals *locals, int set)
{
	if (set == 0)
		locals->fd_out = open(tmp->operator->content,O_APPEND | O_CREAT | O_WRONLY, 0777);
	else if (set == 1)
	{
		if (locals->fd_out > 1)
			close(locals->fd_out);
		return (safe_fd_set(&locals->fd_out, open(
					tmp->operator->content,
					O_APPEND | O_CREAT | O_WRONLY, 0777)));
	}
	return (1);
}
