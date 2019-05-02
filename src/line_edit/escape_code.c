/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   escape_code.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 15:05:59 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 07:29:34 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		right_arrow(char *buf, t_pos *pos)
{
	(void)buf;
	if (pos->act_co == pos->max_co - 1 || pos->ans[pos->let_nb] == '\n')
	{
		pos->act_co = 0;
		pos->act_li += 1;
	}
	else
		pos->act_co++;
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
	pos->let_nb++;
}

void		left_arrow(char *buf, t_pos *pos)
{
	if (pos->act_co == 0 && pos->act_li == 0)
		return ;
	(void)buf;
	if (pos->act_co == 0 && pos->act_li > pos->start_li)
	{
		pos->act_li--;
		if (pos->ans[pos->let_nb - 1] == '\n')
			pos->act_co = len_of_previous_line(pos);
		else
			pos->act_co = pos->max_co - 1;
	}
	else if (pos->is_complete == 0 && pos->let_nb > 0 &&
		pos->ans[pos->let_nb - 1] == '\n' && pos->act_co == pos->len_prompt)
		return ;
	else
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
	pos->let_nb -= 1;
}

t_hist		*escape_code(char *buf, t_pos *pos, t_hist *hist)
{
	if ((buf && buf[1] == 27) || ft_strncmp(buf + 1, "[F", 2) == 0 || ft_strncmp(buf + 1, "[H", 2) == 0)
		find_jump(buf, pos);
	if (ft_strncmp(buf + 1, "[A", 2) == 0)
		hist = move_through_history(hist, pos, "up", buf);
	else if (ft_strncmp(buf + 1, "[B", 2) == 0)
		hist = move_through_history(hist, pos, "down", buf);
	if (pos->let_nb < (int)ft_strlen(pos->ans) &&
			ft_strncmp(buf + 1, "[C", 2) == 0)
		right_arrow(buf, pos);
	else if (pos->let_nb > 0 && ft_strncmp(buf + 1, "[D", 2) == 0)
		left_arrow(buf, pos);
	else if (pos->let_nb < (int)ft_strlen(pos->ans) && buf[1] == 91 &&
			buf[2] == 51)
		input_is_delete(pos);
	if (ft_strcmp(buf + 1, "[D") == 0 || ft_strcmp(buf + 1, "[C") == 0)
		pos->ans_printed = 1;
	return (hist);
}
