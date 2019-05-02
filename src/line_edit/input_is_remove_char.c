/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_is_remove_char.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 08:12:16 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 14:48:55 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		input_is_delete(t_pos *pos)
{
	char	*swap;

	swap = ft_strnew(pos->let_nb + 1);
	swap = ft_strncpy(swap, pos->ans, pos->let_nb);
	swap = ft_strjoinf(swap, pos->ans + pos->let_nb + 1, 1);
	free(pos->ans);
	pos->ans = swap;
}

void		remove_char_ans(t_pos *pos)
{
	char	*swap;

	swap = ft_strnew(pos->let_nb);
	swap = ft_strncpy(swap, pos->ans, pos->let_nb - 1);
	if (pos->let_nb < pos->len_ans)
	{
		swap = ft_strjoinf(swap, pos->ans + pos->let_nb, 1);
		free(pos->ans);
	}
	pos->ans = swap;
}

void		input_is_backspace(t_pos *pos)
{
	if ((pos->act_co == 0 && pos->act_li == 0) || pos->let_nb == 0)
	{
		pos->ans_printed = 1;
		return ;
	}
	if (pos->act_co == 0 && pos->act_li > pos->start_li)
	{
		pos->act_li -= 1;
		if (pos->ans[pos->let_nb - 1] == '\n')
			pos->act_co = len_of_previous_line(pos);
		else
			pos->act_co = pos->max_co - 1;
	}
	else if (pos->is_complete == 0 && pos->let_nb > 0 &&
		pos->ans[pos->let_nb - 1] == '\n' && pos->act_co == pos->len_prompt)
	{
		pos->ans_printed = 1;
		return ;
	}
	else
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li),
		1, ft_putchar);
	remove_char_ans(pos);
	pos->let_nb -= 1;
	pos->len_ans -= 1;
}
