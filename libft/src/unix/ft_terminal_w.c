/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_terminal_w.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/13 23:12:43 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 01:39:26 by shthevak    ###    #+. /#+    ###.fr     */
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
