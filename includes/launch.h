/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/13 17:29:49 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/16 13:11:19 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LAUNCH_H
# define LAUNCH_H

# include "ft_str.h"
# include "ft_unix.h"
# include "ft_list.h"
# include "ft_mem.h"

/*
********************************************************************************
**                                                                     Defines *
********************************************************************************
*/

# define HISTORY ".42_history"
# define ALIAS ".42_alias"
# define ENV_VAR 0
# define SHELL_VAR 1
# define ALIAS_VAR 2

/*
********************************************************************************
**                                                                  Structures *
********************************************************************************
*/

typedef struct	s_ft
{
	t_var		*env;
	int			env_nb;
	t_list		*his;
	int			fd_his;
	int			fd_alias;
}				t_ft;

/*
********************************************************************************
**                                                                   Fonctions *
********************************************************************************
*/

void			ft_print_shell(void);
void			ft_print_shell_a(int w);
void			ft_print_shell_b(int w);
void			ft_print_shell_c(int w);
void			ft_print_shell_d(int w);
void			ft_print_shell_e(int w);

t_ft			*ft_getstruct(char **env);

void			ft_error(int nb);
void			ft_error_quit(int nb, t_ft *ft);

void			ft_free_struct(void);
void			ft_free_env(void);

int				ft_get_env(char **env, t_var **var);

void			get_history(t_ft *ft);
void			read_history(t_ft *ft);
void			save_history(t_ft *ft);
void			write_history(t_ft *ft);

void			get_alias(t_ft *ft);
void			read_alias(t_ft *ft);
void			save_alias(t_ft *ft);
void			write_alias(t_ft *ft);
#endif
