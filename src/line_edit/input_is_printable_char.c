/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_is_printable_char.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 14:48:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/04 10:16:20 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void			input_is_a_string_of_printable_char(t_pos *pos, char *to_add)
{
	int			j;
	char		buf[2];

	j = 0;
	buf[1] = '\0';
	while (to_add[j])
	{
		buf[0] = to_add[j];
		input_is_printable_char(pos, buf);
		j += 1;
	}
}

static void		fill_char_ans(char *buf, t_pos *pos)
{
	char	*swap;

	swap = NULL;
	if ((pos->let_nb == (int)ft_strlen(pos->ans)) || (pos->is_complete == 0 &&
				ft_strcmp(buf, "\n") == 0))
		pos->ans = ft_strjoinf(pos->ans, buf, 1);
	else
	{
		swap = ft_strnew(pos->let_nb + 1);
		swap = ft_strncpy(swap, pos->ans, pos->let_nb);
		swap = ft_strjoinf(swap, buf, 1);
		swap = ft_strjoinf(swap, pos->ans + pos->let_nb, 1);
		free(pos->ans);
		pos->ans = swap;
	}
	if (pos->is_complete == 0 && ft_strcmp(buf, "\n") == 0)
		pos->let_nb = (int)ft_strlen(pos->ans) - 1;
}

void			prompt_is_on_last_char(t_pos *pos)
{
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co + 1, pos->max_li + 1),
			1, ft_putchar);
	write(1, "\n", 1);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	pos->start_li -= 1;
}

void			input_is_printable_char(t_pos *pos, char *buf)
{
	pos->history_mode = 1;
	fill_char_ans(buf, pos);
	if (pos->act_co == pos->max_co - 1)
	{
		pos->act_co = 0;
		if (pos->act_li == pos->max_li)
			prompt_is_on_last_char(pos);
		else
			pos->act_li += 1;
	}
	else if (pos->start_li + get_len_with_lines(pos) /
			pos->max_co == pos->max_li + 1)
	{
		if (pos->act_co != pos->max_co)
			pos->act_li -= 1;
		pos->act_co += 1;
		prompt_is_on_last_char(pos);
	}
	else
		pos->act_co += 1;
	pos->let_nb += 1;
	pos->len_ans += 1;
}
