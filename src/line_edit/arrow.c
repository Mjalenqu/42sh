/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arrow.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/26 16:35:58 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 19:39:04 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	do_up(t_all *all)
{
	if (all->last && all->last->prev != NULL)
		all->last = all->last->prev;
}

void	do_down(t_all *all)
{
	if (all->last && all->last->next != NULL)
		all->last = all->last->next;
}

void	do_left(t_all *all)
{
	(void)all;
	ft_putstr("LEFT");
}

void	do_right(t_all *all)
{
	(void)all;
	ft_putstr("RIGHT");
}
