/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jump.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 14:23:16 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/23 14:03:40 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static void		jump_left(t_pos *pos)
{
	if (pos->is_complete == 0 && pos->act_co == 2)
		return ;
	if (pos->let_nb == 0)
		return ;
	if (ft_isspace(pos->ans[pos->let_nb]) == 0 &&
			ft_isspace(pos->ans[pos->let_nb - 1]) == 1)
	{
		pos->let_nb--;
		pos->act_co--;
	}
	if (ft_isspace(pos->ans[pos->let_nb]) == 1)
		while (pos->let_nb > 0 && ft_isspace(pos->ans[pos->let_nb]) == 1)
			left_arrow(pos);
	while (pos->let_nb > 0 && ft_isspace(pos->ans[pos->let_nb - 1]) == 0)
		pos->let_nb -= 1;
	short_update(pos, go_to_let_nb(pos));
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

static void		jump_right(t_pos *pos)
{
	if (pos->let_nb >= pos->len_ans)
		return ;
	if (pos->is_complete == 0 && pos->ans && pos->let_nb > 0 &&
			pos->ans[pos->let_nb] == '\n')
		return ;
	if (pos->ans[pos->let_nb] && ft_isspace(pos->ans[pos->let_nb]) == 0)
	{
		while (pos->ans[pos->let_nb] && ft_isspace(pos->ans[pos->let_nb]) == 0)
			right_arrow(pos);
	}
	while (pos->ans[pos->let_nb] && ft_isspace(pos->ans[pos->let_nb]) == 1)
		right_arrow(pos);
}

static void		go_hard_or_go_home(t_pos *pos, char *usage)
{
	if (ft_strcmp(usage, "home") == 0)
	{
		if (pos->is_complete == 0)
		{
			while (pos->let_nb > 0 && (pos->ans[pos->let_nb - 1] != '\n'))
				left_arrow(pos);
		}
		else
		{
			pos->act_co = pos->start_co;
			pos->act_li = pos->start_li;
			pos->let_nb = 0;
		}
	}
	else if (ft_strcmp(usage, "end") == 0)
	{
		pos->let_nb = ft_strlen(pos->ans);
		short_update(pos, go_to_let_nb(pos));
	}
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

void			find_jump(char *buf, t_pos *pos)
{
	int		nb_line;

	pos->ans_printed = 1;
	nb_line = pos->start_li + get_len_with_lines(pos) / pos->max_co;
	if (ft_strcmp(buf + 2, "[A") == 0 && pos->act_li > pos->start_li)
		jump_up(pos);
	if (ft_strcmp(buf + 2, "[B") == 0 && nb_line > pos->act_li)
		jump_down(pos);
	if (ft_strcmp(buf + 2, "[D") == 0)
		jump_left(pos);
	else if (ft_strcmp(buf + 2, "[C") == 0)
		jump_right(pos);
	else if (ft_strcmp(buf + 1, "[F") == 0)
		go_hard_or_go_home(pos, "end");
	else if (ft_strcmp(buf + 1, "[H") == 0)
		go_hard_or_go_home(pos, "home");
}
