/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   copy.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 14:22:14 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 13:38:30 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		print_from_begin(t_pos *pos)
{
	clean_at_start(pos);
	print_ans(pos, 0, pos->start_co);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

void		display_line(t_pos *pos)
{
	int		len;

	len = 0;
	if (pos->start_select == -1)
		return ;
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	if (pos->let_nb_saved == 0)
	{
		clean_at_start(pos);
		print_ans(pos, 0, pos->start_co);
	}
	else
	{
		len = go_to_let_nb_saved(pos);
		tputs(tgoto(tgetstr("cm", NULL), len % pos->max_co, pos->start_li +
					len / pos->max_co), 1, ft_putchar);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		print_ans(pos, pos->let_nb_saved, len % pos->max_co);
	}
	tputs(tgetstr("me", NULL), 1, ft_putchar);
}

void		select_left(t_pos *pos)
{
	if (pos->let_nb == 0)
		return ;
	if (pos->start_select == -1)
		pos->start_select = pos->let_nb;
	left_arrow(pos);
}

void		select_right(t_pos *pos)
{
	if (pos->let_nb >= (int)ft_strlen(pos->ans))
		return ;
	if (pos->start_select == -1)
		pos->start_select = pos->let_nb;
	right_arrow(pos);
}

void		selection_check(t_pos *pos, char *buf)
{
	if (!pos->ans || pos->ans[0] == '\0')
		return ;
	if (pos->start_select != -1 && is_select(buf, pos) == 0)
		print_from_begin(pos);
	if (is_select(buf, pos) == 1)
		selected(pos, buf);
	else
		pos->start_select = -1;
}
