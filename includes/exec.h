/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 13:44:02 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 12:32:29 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include "builtin.h"
# include <signal.h>
# include <fcntl.h>

# include "../libft/includes/ft_str.h"

# define STOPED 1
# define FINISHED 1
# define WRITE_END 1
# define READ_END 0
# define PATH_HEREDOC "/tmp/heredoc"

typedef struct s_lexeur	t_lexeur;
typedef struct s_var	t_var;
typedef struct s_pos	t_pos;

typedef	struct			s_fd
{
	int					old_fd;
	int					new_fd;
	int					is_builtin;
	int					error;
	char				*token;
	struct s_fd			*next;
}						t_fd;

typedef	struct			s_redirect
{
	char				*fd_in;
	char				*fd_out;
	char				*heredoc_content;
	int					fd;
	int					open_in;
	int					open_out;
	char				*token;
	struct s_redirect	*next;
}						t_redirect;

typedef	struct			s_process
{
	struct s_process	*next;
	char				**cmd;
	pid_t				pid;
	char				status;
	char				split;
	int					ret;
	int					completed;
	int					stoped;
	int					builtin;
	int					fd_in;
	int					fd_out;
	int					fd_error;
	int					file_in;
	int					file_out;
	int					background;
	char				*hash_error;
	int					exec_builtin;
	t_redirect			*redirect;
	int					printed;
}						t_process;

typedef struct			s_job
{
	struct s_job		*next;
	t_process			*p;
	pid_t				pgid;
	char				split;
	char				status;
	int					notified;
	int					id;
	char				current;
	int					was_a_plus;
}						t_job;

typedef struct			s_job_list
{
	struct s_job_list	*next;
	struct s_job_list	*prev;
	t_job				*j;
}						t_job_list;

typedef struct			s_save_job
{
	char				current;
	int					was_a_plus;
	struct s_save_job	*next;
	struct s_save_job	*prev;
}						t_save_job;

typedef struct			s_pid_launch
{
	int					pid;
	struct s_pid_launch	*next;
	struct s_pid_launch	*prev;
}						t_pid_launch;

void					print_complete_process(t_process *p);

/*
**	ZOMBIE_C
*/

void					kill_zombie(t_pid_launch *spid, t_job_list *jb);
void					free_pid_launch(void);
void					remember_pid(int pid);
t_pid_launch			*add_list_back_pid_launch(t_pid_launch *spid, int pid);

/*
**	NEW_JOB_C
*/

t_save_job				*copy_job_list(t_job_list *save, t_save_job *head);
void					free_copy_job(t_save_job *copy);
void					add_job(t_job *j, int i);

/*
**	JOB_FUNCTION_PLUS_AND_MINUS_C
*/

t_save_job				*stock_t_job(t_save_job *stock, int usage);
int						place_minus_before_plus_check_null(t_job_list *save,
						int check);
int						place_minus_before_plus(t_job_list *save);
void					replace_plus_and_minus(t_job_list *start);
int						lenlist(t_job_list *start, t_save_job *copy, int usage);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 exec.c                                     ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int						start_exec(t_lexeur **res, t_var *var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 process.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					fill_process(t_job *j, t_lexeur **res, int i);
void					fill_token(t_process *p, t_lexeur **res, int *i);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                         process_file.c                                     ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					fill_process_split(t_job **j, t_lexeur **res, int i);
char					*add_space_content(char *content);
char					*get_content(char *tag, t_lexeur **res, int *t);
void					make_tmp_great_again(t_redirect **tmp);
void					add_heredoc(char *tag, t_lexeur **res, int *i);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                            process_tool.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int						cnt_process(t_lexeur **res, int i);
void					change_job(t_job **j, t_process **start);
int						check_moove_index(t_lexeur **res, int *t);
t_redirect				*init_var(int *t, int *i);
int						check_token_in_condition(t_lexeur **res, int t);
/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                            process_fill.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					fill_process_split(t_job **j, t_lexeur **res, int i);
void					fill_token(t_process *p, t_lexeur **res, int *i);
int						fill_ag_first(t_redirect *tmp, t_lexeur **res, int *t);
int						fill_ag_next(t_redirect *tmp, t_lexeur **res, int *t);
void					fill_all_cmd(t_lexeur **res, t_job **j, int *k, int i);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   quote.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int						go_next_token(t_lexeur **res, int *t);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 exec_main.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					launch_job(t_job *j, t_var *var, t_pos *pos,
						t_process *p);
int						ft_test_path(t_process *p, t_var *var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 exec_tool.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					init_job(t_job *j);
void					fill_job(t_job *j, t_lexeur **res);
void					free_lexeur(t_lexeur **res);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 tools.c       	                           ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char					*ft_join_env(char *s1, char const *s2);
char					**split_env(t_var *var);
char					*strjoin_path(char *s1, char *s2);
int						use_execve_acces(char *tmp, char **res, t_var *l_var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 tools.c       	                           ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					cnf_print_error(char *str);
void					ft_tabfree(char **res);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 option_exec.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int						main_option_exec(t_process **first, t_process **second,
						t_var *var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                          alias_norme.c                                     ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					free_one(t_var *var);
/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                          alias_reduction.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int						print_alias(t_var *var);
int						check_name(char *name);
int						print_err(char *name, char *data);
void					ft_free_deux(char *s, char *s1);
int						error_unlias(char *str);
/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                    alias.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int						main_alias(t_process *p, t_var **var);
int						main_unalias(t_process *p, t_var **var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                    alias.c                                 ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
void					add_alias(t_var **var, char *name, char *data);
int						find_alias(t_process *p, int k);
int						looking_for_aliases(t_process *p, int k,
						char *name, char *data);
void					add_list_alias(t_var **var, char *name, char *data);
void					put_foreground(t_job *j, t_var **var, t_process *p);
void					put_background(t_job *j);
int						test_builtin(t_process *p);
int						find_builtins(t_process *p, t_var **var);
int						fork_simple(t_job *j, t_process *p, t_var **var,
						char *cmd_path);
int						ft_execute_function(char *path, char **arg, t_var *var);
void					wait_process(t_var **var);
void					print_start_process(t_job *j);
void					check_zombie();
void					print_job(t_job *j);
void					remove_job(int id, int i);
void					set_job_status(pid_t id, char status);
int						find_job_pgid(pid_t pgid);
void					job_notification(t_var **var);
void					update_status(t_var **var);

int						mark_process_status(pid_t pid, int status, t_var **var);
void					signal_handler();
int						job_is_stoped(t_job *j);
t_job					*find_job_by_id(char *argv);
void					free_lexeur(t_lexeur **res);
void					add_local(t_var **var, char *str, t_var *prev,
						int type);
char					**check_exec_var(char **cmd, t_var **var);
void					free_temp(t_var **var);
int						check_cmd(char **str);
int						find_equal(char *str);
int						launch_redirection(t_process *p);
void					remove_item_var(t_var **var);
void					before_redirection(t_process *p);
t_process				*get_and_or(t_process *p);
int						is_builtin_modify(t_process *p);
void					wait_process_pid(int pid, t_var **var);
void					free_job(t_job *j);
int						duplication(t_redirect *redirect, int fd_in,
						int fd_out);
int						fd_right(char *path);
void					free_job_list(int i);
int						check_name(char *name);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               var_norme.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					add_env_temp(t_var **var, char *str, int type);
char					**remove_tab(char **src, int j);
t_var					*add_one(char *str, char *name);
int						add_env_check(char *name, t_var **var, char *str);

int						check_process(t_var *var, t_process *p, t_job *j);
t_process				*init_launch_job(t_job *j, int *infile);
void					launch_simple_job(t_process *p, t_job *j, t_var **var);
void					alert_job(t_job *j);
void					fill_heredoc_init(t_lexeur **res, t_redirect *tmp,
						int *t);
int						launch_redirection_builtin(t_process *p);

/*
**	HANDLE_PROCESS_C
*/

int						launch_process(t_process *p, t_var *var, char *path);
int						finish_process(t_process *p, t_var *var, char *path);

/*
**	BUILTIN_REDIRECTION_PREPARE_C
*/

int						check_fd_out_content_before_redirection(t_process *p,
						t_redirect *redirect);
int						is_all_num(char *str);

/*
**	REDIRECTION_AGGREGATOR_C
*/

void					init_fd_in_and_out(t_lexeur **res, int *t, t_redirect
						*tmp);

/*
** REDIRECTION_DISPATCH_C
*/

char					*del_back_slash_and_quote_red(char *ar);
void					get_all_redirections_done(t_process *p, t_pos *pos,
						t_redirect *red, int is_builtin);
void					redirect_heredoc(t_fd *fd, t_redirect *red);
void					dispatch_redirection_with_token(t_fd *fd,
						t_redirect *red, t_process *p);
int						is_all_num(char *str);

/*
**	REDIRECTION_INIT_AND_NORMAL_C
*/

void					redirect_simple_right(t_fd *fd, t_redirect *red,
						t_process *p);
void					redirect_simple_left(t_fd *fd, t_redirect *red,
						t_process *p);
t_fd					*add_list_back_fd(t_fd *fd);
void					init_fd_link(t_fd *ne);

/*
**	REDIRECTION_PIPE_AGGREGATOR_C
*/

void					init_pipe_redirection(t_pos *pos, t_process *p,
						int is_builtin, t_fd *fd);
void					end_pipe_redirection(t_pos *pos, t_process *p,
						t_fd *fd, int is_builtin);
void					redirect_aggregator_left(t_fd *fd, t_redirect *red,
						t_process *p);
void					redirect_aggregator_right(t_fd *fd, t_redirect *red,
						t_process *p);
void					redirect_aggregator_minus(t_fd *fd);

/*
**	REDIRECTION_APPLY_C
*/

void					final_change_fd_for_redirections(t_fd *fd, t_pos *pos);
void					dup_fd_for_binaries(t_fd *fd);
int						redirection_get_argument_file_fd(t_redirect *red,
						char *file, t_process *p, int new_fd_out);
int						redirection_find_file_fd(char *file, t_redirect *red,
						t_process *p, t_fd *fd);
void					free_process(t_process *ptr_p);

/*
**	REDIRECTION_FILES_RIGHTS_C
*/

int						check_splited_folds(char *act_fold, char **path, int i,
						t_process *p);
int						check_folders_rights(t_process *p, char *file, int i,
						char *act_fold);

#endif
