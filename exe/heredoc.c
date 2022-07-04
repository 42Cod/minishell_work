/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:44:25 by nkolle            #+#    #+#             */
/*   Updated: 2022/06/03 05:13:02 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_heredoc(t_operator *operator)
{
	char	*line;
	t_sb	prompt_input;
	int		i;

	i = 0;
	sb_create(&prompt_input);
	while (1)
	{
		line = readline(">");
		i++;
		if (line == NULL)
			break ;
		if (ft_strcmp(line, operator->content) == 0)
			break ;
		sb_append_string(&prompt_input, line);
		sb_append_char(&prompt_input, '\n');
		free(line);
		line = NULL;
	}
	free(operator->content);
	operator->content = sb_finalize(&prompt_input);
	operator->redir_type = NOTHING;
	sb_destroy(&prompt_input);
}
