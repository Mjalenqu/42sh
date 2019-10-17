/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_error.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/02 16:17:13 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 13:53:00 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CHECK_ERROR_H
# define CHECK_ERROR_H

# include "../libft/includes/ft_int.h"
# include "../libft/includes/ft_str.h"
# include "../libft/includes/ft_unix.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "lexeur.h"

# define ERROR "\033[1;31m"
# define WHITE "\033[0m"

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 error.c                                    ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			check_error(char *str);
int			error_before_lexer(char **str);
int			error_lex(t_lexeur **lex);
int			syntax_print_error(int token);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              error_tool.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
void		error_heredoc_go_next(char *str, int *i);
int			first_check(char *str, int i, int token);
int			second_check(char *str, int i, int token);
void		moove_next_quote(char c, char *str, int *i);
#endif
