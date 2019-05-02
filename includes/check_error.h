/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_error.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/02 16:17:13 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 13:25:19 by mjalenqu    ###    #+. /#+    ###.fr     */
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

# define ERROR "\033[1;31m"
# define WHITE "\033[0m"

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 error.c                                    ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int			check_error(char *str);

#endif