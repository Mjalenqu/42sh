/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 18:08:47 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:06:45 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

# include "../libft/includes/ft_str.h"
# include "../libft/includes/ft_int.h"
# include "../libft/includes/ft_unix.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/ft_mem.h"
# include "../libft/includes/ft_printf_err.h"
# include <stdio.h>

typedef struct s_temp_var	t_tvar;

typedef struct		s_alias
{
	char			*data;
	struct s_alias	*next;
	struct s_alias	*prev;
}					t_alias;

char				check_last_char(t_alias *alias, int j);
void				fill_alias(char *str, t_alias *alias);
void				free_array(char ***array);
int					end(char **str);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                            free_file.c                                     ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void				free_list(t_alias *alias);
void				free_ar(char **str);
void				free_list_tvar(t_tvar *alias);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                         alias_change_type.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_alias				*make_ar_to_list(char **str);
char				**make_list_to_ar(t_alias *alias);
int					check_simple_or_multiple(char *str);
char				*del_space(char *str);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               alias_cnt.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int					cnt_list(t_alias *alias);
int					cnt_array(char **str);
void				fill_alias_solo(char *str, t_alias *alias);
void				ft_add_list(t_alias *alias, int i, char *str);
void				fill_alias_multiple(char *str, t_alias *alias, int *i);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  var_tool.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int					cnt_list_var(t_tvar *var);
char				**make_list_to_ar_var(t_tvar *alias);
t_tvar				*make_ar_to_list_var(char **str);
void				del_all_backslash(t_alias *al);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                        var_condition_tool.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void				condition_simple_quote(char *str, int *i);
int					condition_find_dollar(char *str, int i);
#endif
