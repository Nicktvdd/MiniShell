/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:44:28 by nvan-den          #+#    #+#             */
/*   Updated: 2023/08/31 13:16:11 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

# define WORD 0
# define PIPE 1
# define LEFT_R 2
# define RIGH_R 3
# define HEREDOC 4
# define APPEND 5
# define PATH_MAX 4096

typedef struct s_redirec
{
	char				*token;
	char				*hd_file_name;
	int					type;
	struct s_redirec	*next;
	struct s_redirec	*prev;
}						t_redirec;

typedef struct s_token
{
	char				*tokens;
	int					type;
	int					index;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_cmd
{
	char				**commands;
	t_token				*tok_struct;
	t_redirec			*redirections;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_data
{
	char				**env;
	int					pipex;
	t_cmd				*struc_cmd;
	char				*line_read;
	t_token				*struc_tok;
}						t_data;

typedef struct s_global
{
	int					g_exit_status;
	int					heredoc_signal;
}						t_global;

/* extern  */t_global				g_var;

/*Error msg and free*/
void					error_msg(char *msg);
void					error_msg_noexit(char *msg, int exit_status);
void					error_msg_command(char *msg, char *command);
void					reset(t_data *data);
void					error_msg_redic(char *msg, char *input,
							int exit_status);
void					error_msg_parser(t_data *data, char *msg, int type);
void					error_msg_export(char *msg, char *input);

/*Builtins*/
int						is_builtin(char *str);
char					**ft_unset(char *cmd, char**env);
int						ft_pwd(void);
int						ft_cd(char **args, t_data *data);
char					**go_home(char **env);
void					update_path(char *key, char *path, t_data *data);
int						ft_export(char **arg, t_data *data);
void					ft_env(char **env);
char					**handle_args(char *arg, t_data *data);
char					**modify_env_var(t_data *data, char *arg, int len);
int						content_check(char *str);
int						is_first_alpha(char *arg);
int						match_env_key(char *arg, t_data *data, \
										int index, int len);
char					*get_string(char *arg);
char					*get_key(char *arg);
int						ft_keylen(char *arg);
char					*combine_str(const char *str, const char *key);
int						run_builtin(t_data *data, char **cmds);
int						ft_echo(char **argv);
int						env_builtin(t_data *data, char **cmds);
int						is_env_builtin(char *str);
int						run_cmd(char **cmd, int index, t_data *data);
int						cmd_cmp(const char *str1, const char *str2);
int						ft_exit(t_data *data, char **argv);
int						is_numeric_parameters(char *param);
int						get_env_var(char *arg, char **env, int index, int len);

/*Signal functions*/
void					signal_in_exec(void);
void					start_signal(void);
void					heredoc_signal(void);
void					hd_handler(int signal);

/* Environment functions */
char					**envdup(char **env);

/*INIT DATA*/

void					init_data(t_data *data);

/*Free stuff*/

void					free_argt(char **argument);
void					reset_cmds(t_cmd **struc_cmd);
void					reset_token(t_token **tokens);
void					reset_tools(t_data *data);
void					reset_redirect(t_redirec **tokens);
void					free_line_input(char *line, char *temp_l);

/*Check input*/
int						check_line(t_data *data, char *line);
int						syntax_redirection(char *line);

/*Tokenization*/
void					tokenization(t_data *data);
int						count_tokens(char *line, char *del);
int						is_whitespace(char *line, int i);
int						check_token_type(char c);
int						tok_closed_quotes(char *str, int i, char quote);
int						operator_type(char operator);
int						check_delimiter(char c, char *delimiter);

/*Parser*/

void					parser(t_data *data);
void					set_number_of_pipes(t_data *data, t_token *tokens);
int						count_commands(t_token *node);
void					parse_redirection(t_data *data, t_token **node,
							t_redirec **redirec);
void					check_redirection(t_token **node);
char					**separete_args(char **str);

/*Executor*/

void					executor(t_data *data);
int						envp_cmd(t_data *data);
int						get_path(t_cmd *cmds, t_data *data);
char					*executable_path(char **commands, t_data *data);
char					**separete_args(char **str);
void					launch_single_cmd(t_cmd *cmds, t_data *data);
int						do_execution(t_cmd *cmds, char *path, t_data *data);
int						get_path(t_cmd *cmds, t_data *data);
void					execute_cmd(t_cmd *cmds, t_data *data);

/*Pipes*/

void					launch_pipes(t_data *data);
void					execute_pipes(t_cmd *cmds, int num_pipes,
							int **pipes, t_data *data);
void					execute_command(int pipe_read_end, int pipe_write_end,
							t_cmd *cmd, t_data *data);
void					create_pipes(int num_pipes, int **pipes);
void					close_pipes(int i, int num_pipes, int **pipes);
void					child_pipe(int i, int num_pipes, int **pipes);
void					close_child_pipes(int num_pipes, int **pipes);

/*Expander*/

void					expander(t_data *data, t_token **token);
int						skip_digit(int i, char *str);
int						is_dollar(char *tok);
int						ft_strcmp(const char *str1, const char *str2);
int						is_equal(char *env);
int						len_equal(char *str);
int						dolar_index(char *str);
int						no_single_quotes(char *str);
char					*get_str(char *str, char c);
int						dollar_tok_len(char *str, int j);
char					*rm_double_quotes(char *str);
char					*rm_single_quotes(char *str);
void					remove_quotes(t_token *current);
char					*replace_dollar(char *str, t_data *data);
int						expand_env(char **temp, int i, t_data *data, char *str);
int						get_exit_status(char **str);
int						export_quotes(char *current, char *next);
int						handle_single_dol(char **str);

/*setup redirections*/

void					input_redirection(t_redirec *input);
void					output_redirection(t_redirec *input);
void					setup_redirections(t_redirec *redirections);
void					setup_heredoc(t_data *data, t_redirec *redirections);
/*Linked list utils*/

void					ft_lstadd_back(t_token **lst, t_token *new);
t_token					*ft_lstlast(t_token *lst);
t_token					*ft_lstnew(char *token, int type, int index);
t_cmd					*cmd_new(char **token, t_redirec *redirec);
t_cmd					*cmd_last(t_cmd *lst);
void					cmd_add_back(t_cmd **lst, t_cmd *new);
int						create_cmd_node(char **sub_line, t_cmd **commands);
t_token					*next_elem(t_token *args);
t_redirec				*redirec_lstnew(char *token, int type);
t_redirec				*redirec_lstlast(t_redirec *lst);
void					redirec_lstadd_back(t_redirec **lst, t_redirec *new);
void					deletenode(t_token **struck_tok, t_token *del);

void					printList(t_token *node);
void					printcmd(t_cmd *node);

#endif
