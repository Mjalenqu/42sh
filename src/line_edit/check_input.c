/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 14:41:17 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 12:45:02 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		update_history(t_pos *pos, t_hist *hist, char *buf)
{
	ft_strdel(&pos->saved_ans);
	if (buf[0] != 10)
		pos->saved_ans = ft_strdup(pos->ans);
	if (hist && hist->next == NULL)
	{
		if (hist->cmd != NULL)
			ft_strdel(&hist->cmd);
		hist->cmd = ft_strdup(pos->ans);
	}
	if (pos->ans[0] == '\0' || (pos->is_complete == 0 && pos->let_nb > 0 &&
		pos->ans[pos->let_nb - 1] == '\n' && pos->act_co == pos->len_prompt))
		pos->history_mode = 0;
}

t_hist		*check_input(char *buf, t_pos *pos, t_hist *hist)
{
	if (buf[0] == 27)
		hist = escape_code(buf, pos, hist);
	else
	{
		ft_bzero(buf + 1, 3);
		if (buf[0] == 127)
			input_is_backspace(pos);
		else if (buf[0] == 10)
			hist = input_is_entry(pos, hist, buf);
		else if (buf[0] != 127 && buf[0] != 10)
			input_is_printable_char(pos, buf);
		update_history(pos, hist, buf);
	}
	if (buf[0] != 10 && pos->ans_printed == 0)
		prepare_to_print(pos, buf);
	pos->ans_printed = 0;
	return (hist);
}
