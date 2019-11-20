/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resize.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/05 11:19:48 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/05 12:34:37 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

static void		horizontal_resize(t_pos *pos, int len)
{
	pos->let_nb = ft_strlen(pos->ans);
	pos->len_ans = pos->let_nb;
	short_update(pos, len);
	clean_at_start(pos);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), 0, pos->start_li), 1, ft_putchar);
	print_prompt(pos);
	if (pos->ctrl_search_history == 1)
	{
		write(1, "(reverse-i-search)'", 19);
		ft_printf("%s':", pos->ans);
		write(1, pos->ctrl_hist_cmd, ft_strlen(pos->ctrl_hist_cmd));
	}
	else
		print_ans(pos, 0, pos->start_co);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
}

static void		vertical_resize(t_pos *pos, int len)
{
	get_cursor_info(pos, &pos->act_li, &pos->act_co, 0);
	pos->start_li = pos->max_li - len / pos->max_co;
	pos->act_li = pos->start_li + go_to_let_nb(pos) / pos->max_co;
}

void			resize_screen(t_pos *pos)
{
	int			save_x;
	int			save_y;
	int			len;

	save_x = pos->max_co;
	save_y = pos->max_li;
	len = get_len_with_lines(pos);
	check_term();
	pos->max_co = tgetnum("co");
	pos->max_li = tgetnum("li") - 1;
	if (save_x != pos->max_co)
		horizontal_resize(pos, len);
	else if (save_y != pos->max_li)
		vertical_resize(pos, len);
}
