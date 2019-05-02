/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   termcaps.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/04 15:55:39 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 11:36:09 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

/*
** includes **
*/

# include <signal.h>
# include <curses.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include "../libft/includes/ft_str.h"
# include "../libft/includes/ft_int.h"
# include "../libft/includes/ft_unix.h"

/*
** structures **
*/

typedef struct			s_count
{
	int					quote;
	int					dquote;
	int					esp;
	int					pipe;
	int					subsh;
	int					cursh;
}						t_count;

typedef struct			s_command
{
	char				*res;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;


typedef struct			s_wind
{
	int					term_fd;
	int					max_col;
	int					max_line;
	int					pos_line;
	int					pos_col;
	int					srt_line;
	int					srt_col;
}						t_wind;

typedef struct			s_select
{
	struct termios		my_term;
	struct termios		old_term;
}						t_select;

typedef struct			s_history
{
	int					len;
	char				*cmd;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct			s_env
{
	char				*name;
	char				*data;
	int					type;
	struct s_env		*next;
}						t_var;

typedef struct			s_all
{
	t_wind				wind;
	t_history			*history;
	t_history			*last;
	t_var				*env;
	t_select			*select;
	t_count				count;
	char				*save;
	char				*prompt;
	int					index;
}						t_all;
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
# define HOME	4741915
# define END	4610843
# define ALT_L    25115
# define ALT_R    26139

# define HIST	".42_history"
/*
# define CMD	all->history->cmd
# define HNEXT	all->history->next
# define HPREV	all->history->prev
# define FD		all->wind->term_fd
# define BSIZE 6
*/
/*
*******************************************************************************
***							init_term.c										***
*******************************************************************************
*/
t_select				*init_term(t_all *all);
int						get_term(void);
int						check_term(void);

/*
*******************************************************************************
***							key_hook.c										***
*******************************************************************************
*/
int						*key_hook(t_all *all);
int						ft_put_c(int c);

/*
*******************************************************************************
***								env.c										***
*******************************************************************************
*/
t_var					*init_env(char **env);
char					*init_name(char *src);
char					*init_data(char *src);

/*
*******************************************************************************
***								windows.c									***
*******************************************************************************
*/
t_wind					init_wind(void);

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
void					get_history(t_history **history);
void					read_history(t_history **history);
int						ft_create_file(char *path);
int						ft_execute(char *exec, char **opt, char **env);
int						ft_file_exists(char *path);
int						ft_file_wrights(char *path);

void					do_up(t_all *all);
void					do_down(t_all *all);
void					do_left(t_all *all);
void					do_right(t_all *all);
void					do_back(t_all *all, char **res);
void					do_del(t_all *all);
void					do_tab(t_all *all);
char					*remove_char(char **str, int i);
t_history				*add_history(t_all *all);
void					write_history(t_all *all);
void					maj_pos(t_all *all);

/*
*******************************************************************************
***								ft_error.c									***
*******************************************************************************
*/
void					free_all(t_all *all);
void					free_env(t_var *var);


void					do_the_enter(t_all **all);

t_all					*init_all(t_all *all, char **env);
int						main_line_edit(t_all *all);
void					end_of_shell(t_all *all);
#endif
