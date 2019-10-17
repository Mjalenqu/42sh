/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_ans.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 12:07:48 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 08:56:07 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static int		escape_code_complete(t_pos *pos)
{
	int		i;

	i = 0;
	if (pos->start_li < 0)
		pos->start_li = 0;
	tputs(tgoto(tgetstr("cm", NULL),
				pos->start_co, pos->start_li), 1, ft_putchar);
	return (i);
}

static int		incomplete_history(int *act_co, int *act_li, t_pos *pos)
{
	int		i;

	if (pos->start_li < 0)
	{
		pos->let_nb_saved = 0;
		pos->start_li = 0;
	}
	*act_co = go_to_let_nb_saved(pos) % pos->max_co;
	*act_li = pos->start_li + go_to_let_nb_saved(pos) / pos->max_co;
	i = pos->let_nb_saved;
	if (i == -1)
		i = 0;
	tputs(tgoto(tgetstr("cm", NULL), *act_co, *act_li), 1, ft_putchar);
	return (i);
}

static int		global_case(int *act_co, int *act_li, char *buf, t_pos *pos)
{
	int		i;

	if (*act_co == 0 || (pos->is_complete == 0 && pos->let_nb > 0 &&
			pos->ans[pos->let_nb - 1] == '\n' && *act_co == pos->len_prompt))
	{
		*act_co = pos->max_co - 1;
		*act_li = *act_li - 1;
	}
	else
		*act_co = *act_co - 1;
	if (*act_co == pos->len_prompt - 1 && buf[0] == 127)
		*act_co = pos->len_prompt;
	i = pos->let_nb - 1;
	if (i == -1)
		i = 0;
	tputs(tgoto(tgetstr("cm", NULL), *act_co, *act_li), 1, ft_putchar);
	return (i);
}

void			print_ans(t_pos *pos, int i, int act_co)
{
	if (pos->ans && ft_strchr(pos->ans, '\n' != 0))
		write(1, pos->ans + i, ft_strlen(pos->ans) - i);
	else if (pos->ans)
	{
		while (pos->ans[i])
		{
			if (pos->start_select != -1 && is_in_selection_area(i, pos) == 1)
				tputs(tgetstr("mr", NULL), 1, ft_putchar);
			else
				tputs(tgetstr("me", NULL), 1, ft_putchar);
			write(1, &pos->ans[i], 1);
			act_co += 1;
			if (act_co == 1 && pos->ans[i] == '\n' &&
					i > 0 && pos->ans[i - 1] != '\n')
				write(1, "\n", 1);
			if (act_co == pos->max_co || pos->ans[i] == '\n')
				act_co = 0;
			if (pos->ans[i] == '\n' && pos->is_complete == 0)
			{
				write(1, "> ", 2);
				act_co = pos->len_prompt;
			}
			i += 1;
		}
	}
}

void			prepare_to_print(t_pos *pos, char *buf)
{
	int		i;
	int		act_co;
	int		act_li;

	act_co = pos->act_co;
	act_li = pos->act_li;
	if (buf[0] == 27 && pos->is_complete == 1)
		i = escape_code_complete(pos);
	else if (pos->is_complete == 0 && buf[0] == 27 &&
		(ft_strcmp(buf + 1, "[A") == 0 || ft_strcmp(buf + 1, "[B") == 0))
		i = incomplete_history(&act_co, &act_li, pos);
	else
		i = global_case(&act_co, &act_li, buf, pos);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	if (buf[0] == 27 && pos->is_complete == 1)
		print_ans(pos, i, pos->start_co);
	else
		print_ans(pos, i, act_co);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li),
			1, ft_putchar);
}
