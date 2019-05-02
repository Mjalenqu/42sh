/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   termcaps.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 09:15:13 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 07:30:29 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

// # include "ft_printf.h"
# include "../libft/includes/ft_str.h"
# include "../libft/includes/ft_int.h"
# include "../libft/includes/ft_unix.h"
# include "exec.h"
# include "check_error.h"
# include <stdio.h>
# include <unistd.h>
# include <term.h>
# include <stdlib.h>
# include <curses.h>

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

# define HIST	".42_history"

typedef struct		s_pos
{
	int				act_co;
	int				act_li;
	int				start_li;
	int				start_co;
	int				max_co;
	int				max_li;
	int				ans_printed;
	char			*ans;
	char			*saved_ans;
	int				is_complete;
	int				was_incomplete;
	int				len_ans;
	int				let_nb;
	int				let_nb_saved;
	int				history;
	int				history_mode;
	int				history_loop;
	char			*prompt;
	int				len_prompt;
	int				debug;
	int				debug2;
	int				debug3;
	int				debug4;
	int				debug5;
	struct termios	old_term;
	struct termios	my_term;
}					t_pos;

typedef struct		s_inter
{
	int				sg_quote;
	int				db_quote;
	int				bracket;
	int				parenthesis;
	int				a_quote;
	int				db_and;
	int				pipe;
	int				db_pipe;
}					t_inter;

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


int		get_next_line_42sh(const int fd, char **line);
char	*termcaps42sh(char *prompt, int error, t_pos *pos, t_hist *hist);

/*
**INIT_FT_SELECT.C
*/

void				init_terminfo(t_pos *pos);
int					init_pos(t_pos *pos, char *buf);
void				get_start_info(char *buf, t_pos *pos);
int					check_term(void);

/*
**CHECK_INPUT.C
*/

void				free_t_hist(t_hist *hist);
t_hist				*check_input(char *buf, t_pos *pos, t_hist *hist);

/*
**INPUT_IS_REMOVE_CHAR.C
*/

void				input_is_backspace(t_pos *pos);
void				remove_char_ans(t_pos *pos);
void				input_is_delete(t_pos *pos);

/*
**INPUT_IS_PRINTABLE_CHAR.C
*/

void				prompt_is_on_last_char(t_pos *pos);
void				input_is_printable_char(t_pos *pos, char *buf);

/*
**ESCAPE_CODE.C
*/

t_hist				*escape_code(char *buf, t_pos *pos, t_hist *hist);
void				left_arrow(char *buf, t_pos *pos);
void				right_arrow(char *buf, t_pos *pos);
int					len_of_previous_line(t_pos *pos);

/*
** INPUT_IS_ENTRY.C
*/

t_hist				*input_is_complete(t_pos *pos, t_hist *hist);
t_hist				*input_is_entry(t_pos *pos, t_hist *hist, char *buf);

/*
**HANDLE_ANS.C
*/

void				prepare_to_print(t_pos *pos, char *buf);
void				fill_char_ans(char *buf, t_pos *pos);
void				remove_char_ans(t_pos *pos);
int					get_len_with_lines(t_pos *pos);

/*
**HISTORY.C
*/

void				init_t_hist(t_hist *hist);
t_hist				*create_history(t_pos *pos, t_hist *hist);
t_hist				*add_list_back_hist(t_hist *hist);
void				update_position(t_pos *pos, char *cmd);

/*
**MOVE_THROUGHT_HISTORY.C
*/


t_hist				*move_through_history(t_hist *hist, t_pos *pos, char *usage, char *buf);

/*
**SEARCH_IN_HISTORY.C
*/

t_hist		*search_up_complete_in_history(t_hist *hist, t_pos *pos);
t_hist		*search_down_complete_in_history(t_hist *hist, t_pos *pos);
t_hist		*search_up_incomplete_in_history(t_hist *hist, t_pos *pos);
t_hist		*search_down_incomplete_in_history(t_hist *hist, t_pos *pos);

/*
**TERMCAPS_TOOLS.C
*/

void				print_info(t_pos *pos);
void				print_hist(t_pos *pos, t_hist *hist);

/*
**CALCUL_LINE.C
*/

int					go_to_let_nb_saved(t_pos *pos);
int					count_nb_line(t_pos *pos, int *j);



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
t_var					*init_env(char **env);
char					*init_name(char *src);

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
*******************************************************************************
***								ft_error.c									***
*******************************************************************************
*/
//void					free_all(t_all *all);
void					free_env(t_var *var);

void					find_jump(char *buf, t_pos *pos);

# include "lexeur.h"

#endif
