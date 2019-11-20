/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_terminal_w.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/13 23:12:43 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_unix.h"

int		ft_terminal_w(int fd)
{
	struct winsize	w;

	ioctl(fd, TIOCGWINSZ, &w);
	return (w.ws_col);
}
