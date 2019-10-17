/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   copy_tools.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/24 10:17:12 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 09:35:40 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int		is_select(char *buf, t_pos *pos)
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59)
		return (1);
	pos->start_select = -1;
	return (0);
}

void	selected(t_pos *pos, char *buf)
{
	if (buf[5] == 67)
		select_right(pos);
	else if (buf[5] == 68)
		select_left(pos);
	display_line(pos);
	pos->ans_printed = 1;
}

void	clear_and_print(t_pos *pos)
{
	tputs(tgoto(tgetstr("cm", NULL), pos->start_co, pos->start_li),
			1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	print_ans(pos, 0, pos->start_co);
	pos->ans_printed = 1;
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li),
			1, ft_putchar);
}

void	save_char(t_pos *pos)
{
	char	*save;
	char	*to_free;

	save = NULL;
	to_free = stock(NULL, 4);
	if (to_free)
		free(to_free);
	if (pos->start_select < pos->let_nb)
		save = ft_strndup(pos->ans + pos->start_select,
				pos->let_nb - pos->start_select + 1);
	else
		save = ft_strndup(pos->ans + pos->let_nb,
				pos->start_select - pos->let_nb + 1);
	stock(save, 3);
}
