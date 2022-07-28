/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marius <marius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:49:55 by nmichael          #+#    #+#             */
/*   Updated: 2022/07/13 17:20:22 by marius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_add_hidden_2(t_env2 **env_struct2, char *cmd)
{
	t_env2	*new;
	int		i;

	i = 0;
	new = ft_calloc(1, sizeof(t_env2));
	new->name_hidden = ft_substr(&cmd[i], 0, env_break2(&cmd[i]));
	new->value_hidden = ft_substr(&cmd[i], env_break(&cmd[i]) + 1,
			env_start(&cmd[i]));
	new->hidden = true;
	new->next = NULL;
	ft_lstadd_back_env_hd(env_struct2, new);
	return (SUCCESS);
}

int	env_add_hidden_3(t_env2 **env_struct2, char *cmd)
{
	t_env2	*new;
	int		i;

	i = 0;
	new = ft_calloc(1, sizeof(t_env2));
	new->name_hidden = ft_substr(&cmd[i], 0, ft_strlen(&cmd[i]));
	new->hidden = true;
	new->next = NULL;
	ft_lstadd_back_env_hd(env_struct2, new);
	return (SUCCESS);
}

void	init_locals(t_exe_locals *locals)
{
	locals->i = 0;
	locals->j = 0;
	locals->fd_in = STDIN_FILENO;
	locals->fd_out = STDOUT_FILENO;
	locals->fd_next = 0;
	locals->fd_standard_in = dup(STDIN_FILENO);
	locals->fd_standard_out = dup(STDOUT_FILENO);
	locals->flag_previous_pipe = 0;
	locals->exit_status = 0;
}

int		str_count(t_input **input)
{
	t_env *temp;
	int		i;

	temp = (*(*input)->env);
	i = 0;
	while(temp)
	{
		i++;
		temp = temp->next;
	}
	return(i);
}

char	**char_converter(t_input **input)
{
	int i;
	int j;
	char *str;
	char **arr;
	t_env *env;

	i = 0;
	j = str_count(input);
	env = *((*input)->env);
	arr = ft_calloc(sizeof(char *), j + 1);
	while (env)
	{
		j = 0;
		str = ft_strjoin(env->name, env->value);
		j = ft_strlen(str);
		arr[i] = ft_calloc(sizeof(char), j);
		arr[i] = ft_strdup(str);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

int find_breaking_char(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			break ;
		i++;
	}
	return (i);
}

char *ft_getenv(char *name, t_env2 *env)
{
	while (env)
	{
		if (ft_strncmp(name, env->name_hidden, env_size(env->name_hidden)) == 0)
			return (ft_strdup(env->value_hidden));
		env = env->next;
	}
	return (NULL);
}

int ft_getenv2(char *name, t_env2 *env)
{
	while (env)
	{
		if (ft_strncmp(name, env->name_hidden, env_size(env->name_hidden)) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	check_for_dollar(t_input *input, t_env2 *env2)
{
	t_input	*tmp;
	t_env2	*tmp2;
	int		i;

	tmp = input;
	tmp2 = env2;
	i = 0;
	while (tmp->cmd[i])
	{
		if (ft_strrchr(tmp->cmd[i], '$'))
		{
			if (*(ft_strrchr(tmp->cmd[i], '$') + 1) == '?')
				{
					free(tmp->cmd[i]);
					tmp->cmd[i] = ft_itoa(get_err_code());
				}
			else
			{
				input->buff = get_dollar_in_quotes(env2, tmp->cmd[i]);
				converte_buff(input, &i);
			}
		}
		i++;
	}
}

char	**get_dollar_in_quotes(t_env2 *env2,  char *str)
{
	int		i;
	int		j;
	int		k;
	char	**expanded;
	char	*dollarstr;

	i = 0;
	j = 0;
	k = 0;
	expanded = NULL;
	expanded = malloc(sizeof(char *) * (100));
	while (str[i])
	{
		k = i;
		while (str[i] && (str[i] != '$'))
			i++;
		expanded[j] = ft_substr(str, k, (i - k));
		k = i;
		j++;
		if (str[i] && (str[i] == '$'))
		{
			while (42)
			{
				i++;
				if(str[i] == ' ' || str[i] == '\0' || str[i] == '$')
				{
				dollarstr = ft_substr(str, (k + 1), (i - k - 1));
				if (ft_getenv2(dollarstr, env2) == 0)
					break;
				else
					expanded[j] = ft_strdup(ft_getenv(dollarstr, env2));
					free(dollarstr);
					j++;
					break;
				}
			}
		}
	}
	expanded[j + 1] = NULL;
	return(expanded);
}

void	converte_buff(t_input *input, int *i)
{
	int		j;

	j = 0;
	free(input->cmd[*i]);
	input->cmd[*i] = " ";
	while(input->buff[j] != NULL)
	{
		input->cmd[*i] = ft_strjoin(input->cmd[*i], input->buff[j]);
		free(input->buff[j]);	
		j++;
	}
}