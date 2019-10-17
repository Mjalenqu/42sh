/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 14:01:05 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/12 08:47:27 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft.h"

# define BUFF_SIZE 50000

typedef struct		s_gnlist
{
	int				fd;
	char			*str;
	struct s_gnlist	*next;
}					t_gnlist;

int					get_next_line(const int fd, char **line);

#endif
