/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 11:50:38 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 13:44:16 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "exec.h"
# include "termcaps.h"
# include "hash.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

# define LEN_BUILTIN_LIST 18
# define TERM "42sh"

typedef struct s_var		t_var;
typedef struct s_process	t_process;
typedef struct s_hist		t_hist;
typedef struct s_hash		t_hash;
typedef struct s_job_list	t_job_list;
typedef struct s_job		t_job;
typedef struct s_pos		t_pos;
typedef struct	s_builtin
{
	const char	*name;
	int			(*ptr_builtin)(t_process*, t_var**);
	int			modify_data;
}				t_builtin;

typedef struct	s_fc
{
	char		*flags_model;
	char		*flags;
	char		*ename;
	char		*str_first;
	char		*str_last;
	int			int_first;
	int			int_last;
	int			first_is_str;
	int			last_is_str;
	int			first_not_precised;
	int			last_not_precised;
	int			error;
}				t_fc;

extern const t_builtin	g_builtin_list[LEN_BUILTIN_LIST];

int				ft_test(t_process *p, t_var **var);
int				is_comp(char *op);
int				comp_operator(char *name1, char *type, char *name2, int *error);
int				ft_echo(t_process *p, t_var **var);
int				ft_set(t_process *p, t_var **ptr_var);
int				ft_type(t_process *p, t_var **var);
int				ft_export(t_process *p, t_var **ptr_var);
int				ft_unset(t_process *p, t_var **ptr_var);
char			*ft_get_val(char *name, t_var *var, int type);
int				ft_tabclen(char **array);
void			add_list_env(t_var **var, int type, char *name, char *data);
int				remove_list_var(t_var **ptr_var, int type, char *name);
int				verif_int(char *name, int *error);
int				comp_num_operator(char *name1, char *type, char *name2,
				int *error);

/*
**	FT_FG_BG_PLUS_AND_MINUS_C
*/

t_job_list		*move_plus_and_minus_indicators_moves(t_job_list *save);
void			move_plus_and_minus_indicators(t_job_list *j, t_job_list *save);
void			place_plus_and_minus_init_check(t_job_list *head, int *check);
void			place_plus_and_minus_check_null(t_job_list *head,
				t_job_list *tmp);
void			place_plus_and_minus(t_job_list *head, char split);

/*
**	FT_FG_C
*/

void			put_foreground(t_job *j, t_var **var, t_process *p);
void			move_plus_and_minus_indicators(t_job_list *j, t_job_list *save);
t_job			*find_job_by_id(char *argv);
int				rerun_job(t_job *j, t_var **var, t_process *p);
int				ft_fg(t_process *p, t_var **var);

/*
**	FT_BG_FG_TOOLS_C
*/

t_job			*find_plus(t_job_list *j);
void			go_through_jobs_for_current(t_job_list *j, t_job_list *save);
t_job_list		*find_plus_jb(t_job_list *j);
void			change_plus_and_minus_indicators(t_job_list *jb, t_job *j,
				t_job_list *save);
void			repare_plus_and_minus(t_job_list *save, int check_minus,
				int check_plus);

/*
**	FT_BG_C
*/

t_job_list		*find_plus_jb(t_job_list *j);
int				ft_bg(t_process *p, t_var **var);

/*
**	FT_EXIT_C
*/

void			free_env_list(t_var *var);
int				ft_exit(t_process *p, t_var **var);
/*
**		FT_FC.c
*/

int				ft_fc(t_process *p, t_var **var);
void			check_if_e_flag_induced(t_fc *fc, t_process *p, t_hist *hist);
void			induced_e_flag_check_first_arg(t_fc *fc, t_process *p);

/*
**		FC_TOOLS.C
*/

void			remove_cmd_from_hist(t_hist *hist);
char			*get_program_pwd(char *pwd, int i);
void			overwrite_history_file(t_hist *hist);
void			place_new_cmds_in_history(char **new_cmds, t_hist *hist);
void			print_fc_usage(void);

/*
**		FC_GET_ARGS.C
*/
void			get_str_args_of_fc(t_fc *fc, t_process *p, int i, int check);
void			circle_through_cmd_args(t_fc *fc, t_process *p, int i,
				int check);
void			make_str_arg_into_int(t_fc *fc, t_hist *hist);
void			make_str_last_into_int(t_fc *fc, t_hist *hist);

/*
**		FC_GET_FLAGS.C
*/

int				determ_fc_flags(t_fc *fc, t_process *p, int k, int i);
int				find_flags_order(t_fc *fc, char let_a, char let_b, int usage);

/*
**		FC_EXECUTE_L_FLAG.C
*/

void			prepare_l_flag(t_fc *fc, t_hist *hist);
void			inverse_first_and_last_if_flag_r(t_fc *fc);

/*
**		FC_S_REPLACE_PATTERN.C
*/

char			*replace_cmd_content_with_ename(t_fc *fc, char *tmp_cmd);

/*
**		FC_EXECUTE_S_FLAG.C
*/

void			prepare_s_flag(t_fc *fc, t_hist *hist, t_var **var);

/*
**		FC_EXECUTE_E_FLAG.C
*/

void			send_e_flag_to_exec(t_fc *fc, t_hist *hist, char **env);
void			exec_ide_with_tmp_file(t_fc *fc, int fd, char **env);
void			exec_new_cmds(char **new_cmds);
char			**recover_new_cmds_from_tmp(char **new_cmds, int fd, int i,
				int ret);

/*
**		FC_PREPARE_E_FLAG.C
*/

char			**get_ide_paths(char **env);
void			prepare_e_flag(t_fc *fc, t_hist *hist, t_var **var, int i);
void			correct_int_first_and_int_last_for_e_flag(t_fc *fc,
				t_hist *hist);
char			*check_new_cmd_is_valid(char *new_cmds, char **paths);

/*
**		FC_FREE_C
*/

void			free_fc_struct(t_fc *fc);

/*
**	FT_HASH_C
*/

int				ft_hash(t_process *p, t_var **var);
void			exec_hash_with_flag(t_hash **hash, char flag, char **cmd,
				t_var **var);
void			print_path_hash(t_hash **hash, char **cmd);
void			print_part_of_hash_table(t_hash **hash, char **cmd);

/*
**	HASH_D_FLAG_C
*/

void			remove_selected_entry_hash(t_hash **hash, char **cmd);
void			delete_middle_link(t_hash *tmp);
void			delete_first_link(t_hash **hash, t_hash *tmp, int key);

/*
** FT_SETENV_C
*/

int				ft_setenv(t_process *p, t_var **var);

/*
**	FT_SETENV_TOOL_C
*/

char			**init_al_tab_content(t_process *p, int i);
void			print_env(t_var *var);
int				print_err_setenv(char **al);

/*
** FT_UNSETENV_C
*/

int				ft_unsetenv(t_process *p, t_var **var);

/*
**	FT_ENV_C
*/

int				ft_env(t_process *p, t_var **var);

/*
**	FT_ENV_I_FLAG_C
*/

int				go_through_process_cmd(t_process *p, t_var **new_env,
				t_var **head, int ret);

/*
**	TOOL_C
*/

int				remove_list_var(t_var **ptr_var, int type, char *name);
void			free_name_and_data(char *name, char *data);

/*
**	FT_ENV_TOOLS_C
*/

t_var			*put_new_entry_in_var(t_var *var, char **new_env_entry,
				int usage);
void			free_new_env(t_var *head);
t_var			*init_t_var(t_var *ne);
t_var			*add_list_back_env(t_var *env);

/*
**	FT_CD_C
*/

int				get_cd_option(char **cmd, int *i, int ret, int j);
char			*fill_new_path(char ***tmp, char *new_path, char *cmd,
				t_var **var);
char			*get_path(char *cmd, t_var **var, char *new_path, int option);
void			replace_pwd_vars_in_env(t_var **var, char *new_path,
				int option);
int				ft_cd(t_process *p, t_var **var);

/*
**	FT_CD_PREPARE_DATA_C
*/

char			*move_to_home_dir(t_var **var);
char			*move_to_oldpwd(t_var **var);
char			*replace_double_dot_by_real_path(char *path);
char			*go_to_absolute_path(char *cmd, t_var **var);
char			*move_to_new_dir(char *cmd, t_var **var, char *new_path);

/*
**	FT_CD_VERIF_C
*/

char			*print_pwd(t_var *var);
char			*verif_p_option_path(char *new_path, int i, int absolute);
int				verif_path(char *path, int mute, int usage);
int				check_arguments_number(t_process *p, int *i, int *option);

/*
**	FT_CD_CHECK_CDPATH_C
*/

char			*verif_path_in_cdpath(char *path, t_var *var, char **cmd,
				int j);
void			print_cd_error(char *path, int i, int mute, int usage);
int				finish_ft_cd(char *new_path, t_pos *pos, t_var **var,
				int option);

/*
**	FC_PREPARE_E_FLAG_TOOL.C
*/

char			*check_new_cmd_is_valid(char *new_cmds, char **paths);

/*
**	FT_ENV_I_FLAG_TOOL.C
*/

void			fill_new_link_in_env(t_var *new_env, char **new_env_var);
void			print_new_env(t_var **new_env, t_var **head);

/*
**	FT_JOBS_C
*/

int				ft_jobs(t_process *p, t_var **var);
char			*built_job_name(t_job_list *j, char *name);
int				ft_jobs_option(char **cmd, int *i);

/*
**	FT_JOBS_PRINT_C
*/

void			print_selected_jobs(t_job_list *j, int option, char *arg);
void			print_all_jobs(t_job_list *j, int option);
void			print_current_job(t_job_list *j, int option, char *name);
void			print_status_job(char status);

t_job			*find_plus(t_job_list *j);

#endif
