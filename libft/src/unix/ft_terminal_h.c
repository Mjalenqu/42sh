/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_terminal_h.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/13 23:24:43 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 01:39:06 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_unix.h"

int		ft_terminal_h(int fd)
{
	struct winsize	w;

	ioctl(fd, TIOCGWINSZ, &w);
	return (w.ws_row);
}
