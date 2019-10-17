/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_is_remove_char.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 08:12:16 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/03 07:31:09 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void			input_is_delete(t_pos *pos)
{
	char	*swap;

	swap = ft_strnew(pos->let_nb + 1);
	swap = ft_strncpy(swap, pos->ans, pos->let_nb);
	swap = ft_strjoinf(swap, pos->ans + pos->let_nb + 1, 1);
	free(pos->ans);
	pos->ans = swap;
}

static void		remove_char_ans(t_pos *pos)
{
	char	*swap;

	swap = ft_strnew(pos->let_nb);
	swap = ft_strncpy(swap, pos->ans, pos->let_nb - 1);
	if (pos->let_nb < pos->len_ans)
		swap = ft_strjoinf(swap, pos->ans + pos->let_nb, 1);
	ft_strdel(&pos->ans);
	pos->ans = ft_strdup(swap);
	ft_strdel(&swap);
}

int				input_is_backspace(t_pos *pos)
{
	if ((pos->act_co == 0 && pos->act_li == 0) || pos->let_nb == 0)
		return (1);
	if (pos->act_co == 0 && pos->act_li > pos->start_li)
	{
		pos->act_li -= 1;
		if (pos->ans[pos->let_nb - 1] == '\n')
		{
			pos->act_co = len_of_previous_line(pos);
			if (pos->act_co == pos->max_co)
				pos->act_co = 0;
		}
		else
			pos->act_co = pos->max_co - 1;
	}
	else if (pos->is_complete == 0 && pos->let_nb > 0 &&
		pos->ans[pos->let_nb - 1] == '\n' && pos->act_co == pos->len_prompt)
		return (1);
	else
		pos->act_co -= pos->act_co == 0 ? 0 : 1;
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
	remove_char_ans(pos);
	pos->let_nb -= 1;
	pos->len_ans -= 1;
	return (0);
}
