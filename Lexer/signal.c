/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:41:25 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/03 13:23:39 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prompt(void)
{
	char	*line;
	char	*prompt;
	char	*cwd;
	char	*last;

	line = NULL;
	prompt = "$ ";
	cwd = getcwd(NULL, 0);
	last = ft_strrchr(cwd, '/');
	last++;
	prompt = ft_strjoin(last, prompt);
	free(cwd);
	line = readline(prompt);
	return (line);
}

int	change_ctrlc_sym(bool	value)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	if (value == true)
	{
		attr.c_lflag |= ECHOCTL;
	}
	if (value == false)
	{
		attr.c_lflag &= ~ECHOCTL;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	return (0);
}

void	sig_ctrlc(int sig)
{
	(void)sig;
	if (g_state[0] == HDOC)
	{
		printf("\n");
		prompt();
		close(STDIN_FILENO);
	}
	else
	{
		if (g_state[0] == EXEC)
			printf("^C");
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (g_state[0] == IDLE)
		rl_redisplay();
	g_state[0] = IDLE;
}
