/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:52:51 by nkolle            #+#    #+#             */
/*   Updated: 2022/07/26 15:29:13 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_state[3];

void	read_heredocs(t_input *input)
{
	t_operator	*op;

	while (input != NULL)
	{
		op = input->operator;
		while (op != NULL)
		{
			if (op->redir_type == HEREDOC)
				input_heredoc(op);
			op = op->next;
		}
		input = input->next;
	}
}

int	save_line(t_env *env, t_env2 *env2)
{
	char		*line;
	t_buffer	*buffer;
	t_input		*input;
	const char	*trimmed;

	input = NULL;
	buffer = NULL;
	line = readline("\xf0\x9f\xa6\xa6 ");
	// line = readline("something else -> ");
	trimmed = ft_strtrim(line, " \t\n");
	if (line)
		free(line);
	if (trimmed == NULL)
		return (0);
	if (trimmed[0] != '\0')
	{
		add_history((char *) trimmed);
		parser((char *)trimmed, &buffer, &input, &env);
		read_heredocs(input);
		set_err_code(executer(input, env2));
	}
	return (1);
}

int	main(int ac, char **argv, char **envp)
{
	t_env	*env_struct;
	t_env2	*env_hidden;

	env_struct = NULL;
	env_hidden = NULL;
	(void)argv;
	(void)ac;
	signal(SIGINT, sig_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	change_ctrlc_sym(false);
	env_create_new(&env_struct, envp);
	env_create_new_hidden(&env_hidden, envp);
	while (save_line(env_struct, env_hidden))
		;
	return (0);
}