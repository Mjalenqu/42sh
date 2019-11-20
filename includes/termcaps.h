/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   termcaps.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 09:15:13 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 13:24:19 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include "../libft/includes/ft_str.h"
# include "../libft/includes/ft_int.h"
# include "../libft/includes/ft_unix.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/ft_mem.h"
# include "../libft/includes/ft_printf_err.h"
# include "../libft/includes/ft_printf.h"
# include "exec.h"
# include "check_error.h"
# include "builtin.h"
# include <stdio.h>
# include <unistd.h>
# include <term.h>
# include <stdlib.h>
# include <curses.h>
# include <dirent.h>
# include "lexeur.h"
# include "hash.h"

/*
** color **
*/
# define RESET "\033[00m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define BRED "\033[1;31m"
# define BGREEN "\033[1;32m"
# define BYELLOW "\033[1;33m"
# define BBLUE "\033[1;34m"
# define BPURPLE "\033[1;35m"
# define BCYAN "\033[1;36m"

/*
** key **
*/
# define UP     4283163
# define DOWN   4348699
# define LEFT   4479771
# define RIGHT  4414235
# define TAB    9
# define DEL    2117294875
# define BACK   127
# define ENTER  10
# define ESCAPE 27
# define CTRLUP	2117425947
# define CTRLDOWN	2117491483
# define HOME	4741915
# define END	4610843
# define ALT_L    25115
# define ALT_R    26139

# define HIST		".42_history"
# define RESIZING	28
# define CTRL_C		2

typedef struct s_pid_launch	t_pid_launch;

typedef struct			s_heredoc
{
	char				*to_find;
	int					current_index;
	char				*content;
	struct s_heredoc	*next;
	struct s_heredoc	*prev;
}						t_heredoc;

typedef struct			s_pos
{
	int					act_co;
	int					act_li;
	int					start_li;
	int					start_co;
	int					max_co;
	int					max_li;
	int					ans_printed;
	char				*ans;
	char				*saved_ans;
	int					is_complete;
	int					was_incomplete;
	int					len_ans;
	int					let_nb;
	int					let_nb_saved;
	int					history;
	int					alias;
	int					history_mode;
	int					history_loop;
	char				*prompt;
	int					len_prompt;
	int					start_select;
	int					ctrl_search_history;
	char				*ctrl_hist_cmd;
	int					replace_hist;
	int					error;
	char				*path;
	struct termios		old_term;
	struct termios		my_term;
	int					is_expansion;
	int					active_heredoc;
	char				*ans_heredoc;
	char				*ans_heredoc_save;
	int					last_cmd_on_bg;
	char				*pwd;
	struct s_heredoc	*hdoc;
	int					braceparam;
	int					shtheme;
	int					ret;
	int					act_fd_out;
	int					act_fd_error;
	int					separator;
	int					pipe;
	int					tab_key_printed;
	int					exit_mode;
	int					error_printed;
}						t_pos;

typedef struct			s_htab
{
	struct s_htab		*next;
	struct s_htab		*prev;
	char				*content;
	int					content_type;
	int					content_no;
	int					lenght_max;
	int					matching_index;
}						t_htab;

typedef struct			s_inter
{
	int					sg_quote;
	int					db_quote;
	int					bracket;
	int					parenthesis;
	int					a_quote;
	int					db_and;
	int					pipe;
	int					db_pipe;
}						t_inter;

typedef struct			s_command
{
	char				*res;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct			s_select
{
	struct termios		my_term;
	struct termios		old_term;
}						t_select;

typedef struct			s_var
{
	char				*name;
	char				*data;
	int					type;
	struct s_var		*next;
}						t_var;

typedef struct			s_hist
{
	struct s_hist		*next;
	struct s_hist		*prev;
	char				*cmd;
	int					cmd_no;
}						t_hist;

typedef struct			s_ctrl_hist
{
	int					needle;
	int					act_co;
	int					act_li;
}						t_ctrl_hist;

void					*ft_malloc(size_t size);
void					print_hdoc(t_heredoc *hdoc);
char					*check_path_hash(t_var **var, char *arg, int i,
						char *ans);
void					print_info(t_pos *pos, int usage);
void					print_info2(t_pos *pos);
void					print_hist(t_pos *pos, t_hist *hist);
int						got_a_wildcard(char *name);
int						check_ans(char *str);
void					print_htab_debug(t_htab *htab);
void					print_all_env(t_var *var);

/*
**	RESIZE_C
*/

void					resize_screen(t_pos *pos);

/*
**	PRINT_PROMPT_C
*/

void					print_first_prompt(t_pos *pos);
void					print_second_prompt(t_pos *pos);

void					print_all_env(t_var *var);

/*
**	PRINT_PROMPT_C
*/

void					print_first_prompt(t_pos *pos);
void					print_second_prompt(t_pos *pos);

/*
**	INIT_POS_MAIN_C
*/

void					main_init_pos(t_pos *pos, t_var *my_env);

/*
** CALCUL_LINE
*/

int						get_len_with_lines(t_pos *pos);
int						go_to_let_nb_saved(t_pos *pos);
int						len_of_previous_line(t_pos *pos);
int						count_nb_line(t_pos *pos, int *j);
int						go_to_let_nb(t_pos *pos);

/*
**FT_ERRNO.C
*/

void					error_handling(t_pos *pos, char *variable, int err);

/*
** CHECK_ERROR_C
*/

void					*ft_malloc(size_t size);
int						check_term(void);
int						check_if_process_in_bg(t_pos *pos,
						unsigned char buf[9]);

/*
** CHECK_INPUT.C
*/

t_hist					*check_input(unsigned char *buf, t_pos *pos,
						t_hist *hist);

/*
** ESCAPE_CODE
*/

void					transform_tab_into_space(char *line);
t_hist					*escape_code(char *buf, t_pos *pos, t_hist *hist);
void					right_arrow(t_pos *pos);
void					left_arrow(t_pos *pos);

/*
** HISTORY.C
*/

void					free_t_hist(t_hist *hist);
void					init_t_hist(t_hist *hist);
t_hist					*add_list_back_hist(t_hist *hist);
t_hist					*create_history(t_pos *pos, t_hist *hist);

/*
** INITIALISATION_STOCK
*/

void					get_cursor_info(t_pos *pos, int *li, int *co, int i);
void					init_terminfo(t_pos *pos);
void					init_pos(t_pos *pos, int usage);
void					*stock(void *to_stock, int usage);

/*
** INPUT_IS_ENTRY
*/

t_hist					*entry_is_complete(t_pos *pos, t_hist *hist);
t_hist					*input_is_entry(t_pos *pos, t_hist *hist, char *buf);

/*
** INPUT_IS_PRINTABLE_CHAR
*/

void					input_is_a_string_of_printable_char(t_pos *pos,
						char *to_add);
void					prompt_is_on_last_char(t_pos *pos);
void					input_is_printable_char(t_pos *pos, char *buf);

/*
** INPUT_IS_REMOVE_CHAR
*/

void					input_is_delete(t_pos *pos);
int						input_is_backspace(t_pos *pos);

/*
** MOVE_THROUGHT_HISTORY
*/

t_hist					*move_through_history(t_hist *hist,
						t_pos *pos, char *usage);

/*
** PRINT_ANS
*/

void					prepare_to_print(t_pos *pos, char *buf);
void					print_ans(t_pos *pos, int i, int act_coi);

/*
** SEARCH_IN_HISTORY
*/

t_hist					*search_up_complete_in_history(t_hist *hist,
						t_pos *pos);
t_hist					*search_down_complete_in_history(t_hist *hist,
						t_pos *pos);
void					remove_last_link_hist(void);

/*
** SIGNAL
*/

void					signal_list(void);

/*
** START_TERMCAPS
*/

char					*termcaps42sh(t_pos *pos, t_hist *hist, t_var *var);
void					print_prompt(t_pos *pos);

/*
** TAB_KEY
*/

void					input_is_tab(t_pos *pos);

/*
** TAB_KEY_VAR
*/

t_htab					*looking_for_var(t_pos *pos, t_htab *htab, char **name);

/*
** TAB_KEY_CURRENT_DIR
*/

t_htab					*looking_for_current(t_pos *pos, t_htab *htab,
						char **path, char **name);

/*
** TAB_KEY_ALL_PATH
*/

int						scan_ans_current_file(int *passed_exe, int *ret,
						int i, t_pos *pos);
t_htab					*looking_for_all(t_pos *pos, t_htab *htab, char **name);

/*
** TAB_KEY_TOOLS_CALCUL_PRINT
*/

int						is_a_directory(char *path, t_pos *pos);
int						get_word_index(t_pos *pos);
void					prepare_to_print_htab(t_pos *pos, t_htab *htabi);
void					print_htab(t_htab *htab, int max_word);
void					complete_with_space(t_htab *htab);

/*
** TAB_KEY_TOOLS_MANIP
*/

t_htab					*adjust_lenght_max(t_htab *htab);
char					*get_full_path(t_pos *pos);
char					*get_correct_path(char *path);
void					reduce_ans(t_pos *pos, char *name);
void					add_slash_on_ans(t_pos *pos);

/*
** TAB_KEY_STRUCT
*/

void					free_htab(t_htab *htab);
t_htab					*add_list_back_htab(t_htab *htab);
t_htab					*add_list_back_sort_htab(t_htab *head, t_htab *ls,
						int loop);
t_htab					*fill_new_htab(t_htab *htab, t_htab *neww, int match);

/*
** TAB_KEY_AUTO_COMPLETE
*/

int						wildcard_match(char *s1, char *s2);

t_htab					*get_current_match(t_htab *htab, char *name,
						int wildcard);
void					auto_complete(t_pos *pos, t_htab *htab, char *name,
						char *old_pos_ans);
t_htab					*prepare_auto_complete(t_pos *pos, t_htab *htab,
						char *name);
t_htab					*get_intelligent_match(t_htab *htab, char *name);

/*
** TAB_KEY_AUTO_COMPLETE_FOR_TILDE_C
*/

void					finish_auto_complete(t_pos *pos);
void					reduce_ans_for_tilde(t_pos *pos, char *name);
int						get_length_of_home_env(t_var *env);

/*
** TAB_KEY_SORT
*/

t_htab					*sort_list_htab(t_htab *head);

/*
** TOOLS
*/

void					clean_at_start(t_pos *pos);
void					short_update(t_pos *pos, int len);
void					update_position(t_pos *pos);
int						is_in_selection_area(int i, t_pos *pos);

/*
** COPY a mettre a la norme
*/
void					print_from_begin(t_pos *pos);
void					display_line(t_pos*pos);
void					selection_check(t_pos *pos, char *buf);
void					select_right(t_pos *pos);
void					select_left(t_pos		*pos);

/*
** COPY_TOOLS
*/
int						is_select(char *buf, t_pos *pos);
void					selected(t_pos *pos, char *buf);
void					clear_and_print(t_pos *pos);
void					save_char(t_pos *pos);

/*
** CUT
*/
void					check_copy(unsigned char *buf, t_pos *pos);
void					copy(t_pos *pos);
void					paste(t_pos *pos);
void					cut_char(t_pos *pos);
char					*remove_cut(char *str, int start, int end);

/*
** JUMP a mettre a la norme
*/

void					find_jump(char *buf, t_pos *pos);

/*
**JUMP_UP_DOWN.C
*/

void					jump_down(t_pos *pos);
void					jump_up(t_pos *pos);

/*
** HISTORY_EXPANSION.C
*/
int						check_history_expansion(t_pos *pos, t_hist *hist, int i,
						int error);
int						replace_expansion_by_value(t_pos *pos, t_hist *hist,
						int i, int error);
int						check_if_inside_symbols(char *ans, int i);

/*
** HISTORY_EXPANSION_TYPES.C
*/

int						double_exclamation_expansion(char **new_ans,
						t_hist *hist);
int						number_expansion(char **new_ans, t_hist *hist,
						char *expansion);
int						negative_number_expansion(char **new_ans, t_hist *hist,
						char *expansion);
int						word_finding_expansion(char **new_ans, t_hist *hist,
						char *expansion, t_pos *pos);
int						get_expansion_value(char *expansion, t_hist *hist,
						char **new_ans, t_pos *pos);

/*
** HISTORY_EXPANSION_CALCULATE.C
*/

char					*get_expansion_content(char *ans, int i);
int						get_expansion_length(char *ans, int i);

/*
** init_alias.c
*/
void					init_alias(t_var *var, t_pos *pos, char *line);
void					write_alias(t_var *var, t_pos *p);

/*
*******************************************************************************
***							init_term.c										***
*******************************************************************************
*/
int						get_term(void);
int						check_term(void);

/*
*******************************************************************************
***							key_hook.c										***
*******************************************************************************
*/
int						ft_put_c(int c);

/*
*******************************************************************************
***								env.c										***
*******************************************************************************
*/
t_var					*init_env(char **env, t_pos *pos, char **av, int i);
char					*init_name(char *src);
void					free_env(t_var *ptr_env);
char					*init_data(char *src);
void					shlvl(t_var *env, int ac, char **av);

/*
*******************************************************************************
***								windows.c									***
*******************************************************************************
*/

/*
*******************************************************************************
***								ft_error.c									***
*******************************************************************************
*/
void					ft_error_quit(int nb);
void					ft_error(int nb);

/*
*******************************************************************************
***								history.c									***
*******************************************************************************
*/
int						ft_create_file(char *path);
int						ft_execute(char *exec, char **opt, char **env);
int						ft_file_exists(char *path);
int						ft_file_wrights(char *path);

char					*remove_char(char **str, int i);

/*
**    CONTROL_SEARCH_HISTORY.C
*/

t_hist					*control_search_history(t_pos *pos, t_hist *hist,
						unsigned char *buf);
t_hist					*search_occurence_in_history(t_pos *pos, t_hist *hist,
						t_ctrl_hist *ctrl);
void					needle_found_in_history(t_pos *pos, t_hist *hist,
						t_ctrl_hist *ctrl);
t_hist					*exiting_control_mode(t_pos *pos, t_hist *hist);
int						get_pos_strstr(char *str, char *tofind, int i, int j);

/*
**CONTROL_SEARCH_HISTORY_CALCUL_LINES.C
*/

void					get_right_coordinates_found(t_pos *pos, t_hist *hist,
						t_ctrl_hist *ctrl);
int						count_cmd_line_len(t_pos *pos, char *ans, int act_co);
void					count_ctrl_col_and_line(t_pos *pos, char *ans,
						t_ctrl_hist *ctrl, int needle);
t_hist					*exit_control_search(t_hist *hist, t_pos *pos);

/*
**CONTROL_SEARCH_HISTORY_CALCUL_POS.C
*/

void					get_right_coordinates_not_found(t_pos *pos, t_ctrl_hist
						*ctrl);
void					get_pos_coordinates_right_again(t_pos *pos);

/*
** CHECK_FOR_TILDE_C
*/

int						verif_tilde(char *ans, int i);
char					*check_for_tilde(char *ans, t_var *env, int i,
						int usage);
void					check_copy(unsigned char *buf, t_pos *pos);

/*
** CHECK_BACKSLASH_C
*/

int						count_valid_backslash(int i, char *ans);
int						odd_backslash(int i, char *ans);
char					*check_backslash(t_pos *pos, int i, int j, int count);

/*
**	TOKEN_C
*/

int						add_space(t_pos *pos, int *i);
int						token_condition(char *ans, int i);
int						token(char *ans, t_pos *pos);

/*
**	TOKEN_CONDITIONS_C
*/

int						is_my_index_open(t_pos *pos, int i, char open,
						int limit);
int						simple_pipe(char *ans, int i);
int						double_token(char *ans, int i);
int						brace_param(char *ans, int i);
int						simple_quote(char *ans, int i);
int						double_quote(char *ans, int i);

/*
**	HEREDOC_C
*/

void					check_for_heredoc(t_pos *pos, int i, char open);
void					search_for_heredocs_in_ans(t_pos *pos, int i, int open);
int						fill_hdoc_content(t_pos *pos, char *ans, int i,
						char *tmp);
int						heredoc_found(t_pos *pos, int i, int j);

/*
**	HEREDOC_SEND_VALID_ANS_C
*/

void					heredoc_ctrl_d(t_pos *pos, t_hist **hist);
void					remake_pos_ans(t_pos *pos);
int						fill_ans_heredoc(t_pos *pos, int i, int j);
char					*put_symbol_in_ans(char *ans, int i);
int						check_if_to_find_is_not_empty(t_heredoc *hdoc);

/*
**	HEREDOC_TOOLS_C
*/

char					*remove_backslash(char *ans, int i, int j);
int						going_to_heredoc_end(t_pos *pos, int i);
void					free_hdoc(t_heredoc *hdoc);
t_heredoc				*add_list_back_heredoc(t_heredoc *heredoc);
void					init_t_heredoc(t_heredoc *hdoc);

/*
**	INIT_SPECIAL_PARAMS_C
*/

t_var					*init_spe_params(char **av);
void					*to_stock(void *stock, int usage);

/*
**	FT_PRINTF_FD_C
*/

int						ft_printf_fd(const char *format, ...);
int						print_printf_fd(t_data *data, int i, int fd);
int						iterating_through_output_fd(t_data *data,
						int *printed_backslash, int i, int fd);
int						handle_colors_fd(t_data *d, int i, int tmp, int fd);

/*
**	FT_PRINTF_FD_C
*/

int						ft_printf_err_fd(const char *format, ...);
int						print_printf_err_fd(t_dataerr *data, int i, int fd);
int						iterating_through_output_err_fd(t_dataerr *data,
						int *printed_backslash, int i, int fd);
int						handle_colors_err_fd(t_dataerr *d, int i, int tmp,
						int fd);

#endif
