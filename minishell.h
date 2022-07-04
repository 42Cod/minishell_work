/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmichael <nmichael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:54:19 by nmichael          #+#    #+#             */
/*   Updated: 2022/06/03 13:48:25 by nmichael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define ERROR 1
# define SUCCESS 0
# define PIPE -1

enum e_operator {
	NOTHING,
	INFILE,
	OUT_TRUNCATE,
	HEREDOC,
	OUT_APPEND,
};

typedef struct s_sb
{
	char			*buffer;
	unsigned int	alloc;
	unsigned int	fill;
}	t_sb;

typedef struct s_env
{
	struct s_env	*next;
	char			*value;
	char			*name;
	char			*head;
	bool			hidden;
}				t_env;

typedef struct s_env2
{
	struct s_env2	*next;
	char			*head;
	char			*name_hidden;
	char			*value_hidden;
	bool			hidden;
}				t_env2;

typedef struct s_operator
{
	char				*content;
	enum e_operator		redir_type;
	int					flag;
	int					here_pipe_fd[2];
	struct s_operator	*next;
}	t_operator;

typedef struct s_buffer
{
	char				*content;
	struct s_buffer		*next;
}	t_buffer;

typedef struct s_exe_locals
{
	int		pipe_fd[2];
	pid_t	pid;
	int		flag_previous_pipe;
	int		exit_status;
	int		*pa;
	int		i;
	int		j;
	int		fd_in;
	int		fd_out;
	int		fd_next;
	int		fd_standard_out;
	int		fd_standard_in;
}	t_exe_locals;

typedef struct s_input
{
	char				**cmd;
	struct s_operator	*operator;
	struct s_input		*next;
	struct s_env		**env;
	int					ret;
}	t_input;

enum e_state
{
	IDLE,
	HDOC,
	EXEC
};

extern int	g_state[2];
int			main(int ac, char **argv, char **envp);
int			save_line(t_env *env, t_env2 *env2);
void		parser(char *line_comb, t_buffer **buffer,
				t_input	**input, t_env **env);
char		*read_identifier(char **ptr);
void		read_single_quoted(char **ptr, t_buffer **buffer);
void		read_double_quoted(char **ptr, t_buffer **buffer);
int			is_breaking_char(char **ptr);
int			executer(t_input *input, t_env2 *env2);
int			*process_count(t_input *input, int *j);
int			safe_pipe(int *left, int *right);
void		child_proc(t_input *input, t_exe_locals *locals, t_env2 *env2);
int			exec_redir(t_input *input, t_exe_locals *locals);
int			redirct_stdin(t_input *tmp, t_exe_locals *locals);
int			redirct_std_type_in(t_input *tmp, t_exe_locals *locals);
int			redirct_trunc(t_input *tmp, t_exe_locals *locals);
int			redirct_app(t_input *tmp, t_exe_locals *locals);
void		protected_close(int fd);
char		**char_converter(t_input **input);
int			str_count(t_input **input);
void		init_locals(t_exe_locals *locals);
int			safe_fd_set(int *loc, int value);
void		input_heredoc(t_operator	*operator);
int			env_create(t_env *env_struct, char **env_array);
int			env_break(char *env_array);
int			env_start(char *env_array);
t_env		*ft_lstlast_env(t_env *lst);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
int			stringbuffer_append_char(t_buffer **buffer, char c);
void		append_string_to_linked_list(t_buffer **buffer, char *content);
void		append_string_to_redirection_list(
				t_operator **operator, enum e_operator type, char *content);
t_buffer	*new_element(char *content);
t_operator	*new_element_op(char *content, enum e_operator type);
int			check_for_str(char *s, char *str);
int			check_for_c(const char *s, int c);
void		skip_whitespace(char **line_comb);
void		create_op_files(t_operator **operator);
char		*stringbuffer_create(t_buffer **buffer);
void		stringbuffer_destroy(t_buffer **buffer);
t_buffer	*stringbuffer_create_node(t_buffer **buffer);
void		stringbuffer_get_string(t_buffer **buffer, char **str);
void		ft_lstadd_back_op(t_operator **lst, t_operator *new);
void		ft_lstadd_back_buf(t_buffer **lst, t_buffer *new);
t_buffer	*ft_lstlast_buf(t_buffer *lst);
t_operator	*ft_lstlast_op(t_operator *lst);
void		add_buffer_cmd(t_buffer **buffer, t_input **input);
void		add_operator_cmd(t_operator **operator, t_input **input, int *i);
t_input		*ft_lstlast_cmd(t_input *lst);
void		ft_lstadd_back_cmd(t_input **lst, t_input *new);
t_input		*new_element_cmd(int cmd_length);
void		create_new_input(t_input **input, int cmd_length, t_env **env,
				t_operator **operator);
void		append_linked_list_to_input(t_input **input, t_operator **operator,
				t_buffer **buffer, t_env **env);
char		*find_exec_path(t_input	**input);
char		*find_path(t_input **input);
void		sb_create(t_sb *sb);
void		sb_destroy(t_sb *sb);
void		sb_resize(t_sb *sb, unsigned int size);
void		sb_append_char(t_sb *sb, char c);
void		sb_append_string(t_sb *sb, const char *str);
char		*sb_finalize(t_sb *sb);
int			env_create_new(t_env **env_struct, char **env_array);
int			env_break(char *env_array);
int			env_start(char *env_array);
t_env		*ft_lstlast_env(t_env *lst);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
int			env_create_new_hidden(t_env2 **env_struct, char **env_array);
int			ft_env(t_env *env);
int			ft_strcmp(const char *s1, const char *s2);
int			exec_builtin(t_input **input, t_env *env,
				t_env2 *env2, char **envp);
void		ft_lstadd_back_env_hd(t_env2 **lst, t_env2 *new);
t_env2		*ft_lstlast_env2(t_env2 *lst);
int			env_break2(char *env_array);
int			env_start2(char *env_array);
int			env_add_hidden_2(t_env2 **env_struct2, char *cmd);
void		ft_lstadd_en(t_input *lst, t_env *new);
int			ft_export(t_env *env, t_env2 *env2, t_input **input);
int			env_add_hidden(t_env2 **env_struct2, t_input *input);
int			env_add(t_env **env_struct, char *cmd);
int			is_valid_env(char *env);
int			print_error(int error, char *arg);
void		print4(t_env2 *input);
void		print5(t_env *input);
int			ft_echo(t_input **input);
int			size_arg(t_input **input);
int			ft_pwd(void);
int			env_size(char *env);
void		*ft_memdel(void *ptr);
void		free_node(t_env *env);
int			ft_unset(t_env *env, t_env2 *env2, t_input **input);
int			ft_strisnum(const char *str);
char		*get_path(t_env *env, char *var, int len);
int			oldpwd(t_env *env);
int			to_path(int value, t_env *env);
int			ft_cd(t_input **input, t_env *env);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_exit(t_input *input);
int			ft_strisnum(const char *str);
int			is_builtin(char *cmd);
void		free_node2(t_env2 *env2);
int			env_add_hidden_3(t_env2 **env_struct2, char *cmd);
void		sig_ctrlc(int sig);
int			change_ctrlc_sym(bool	value);
void		check_for_dollar(t_input *input, t_env2 *env2);
void		rd_helper(char **line_comb, t_buffer **buffer);
void		fck_norm1(char **line_comb, t_operator **operator);
void		fck_norm2(char **line_comb, t_operator **operator);
void		fck_norm3(char **line_comb, t_operator **operator);
void		fck_norm4(char **line_comb, t_operator **operator);
void		fck_norm5(char **line_comb, t_buffer **buffer);
void		rd_dollar(char **line_comb, t_buffer **buffer);
int			check_nip(t_input **input);
char		*create_new_putstr(t_input **input);
void		helper_2(t_buffer **buffer, char **line_comb);
void		helper_3(t_buffer **buffer, char **line_comb);
void		helper_4(t_input **input,
				t_operator **operator, t_buffer **buffer, t_env **env);
void		ft_exit2(t_input *input);
void		executer_b(t_exe_locals *locals);
int			executer(t_input *input, t_env2 *env2);
void		child_proc(t_input *input, t_exe_locals *locals, t_env2 *env2);
void		executer_a(t_input *input, t_env2 *env2, t_exe_locals	*locals);
int			executer(t_input *input, t_env2 *env2);
void		executer_b(t_exe_locals *locals);
void		helper6(t_env2 *env2, t_env2 *tmp2);
int			has_slash(t_input **input);

#endif