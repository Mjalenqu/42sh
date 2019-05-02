/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_is_entry.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/24 07:21:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 12:51:37 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int			find_missing_quote(char *str)
{
	int		i;
	int		nb_quote;

	i = 0;
	nb_quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			nb_quote += 1;
		i++;
	}
	if (nb_quote % 2 == 0)
		return (1);
	return (0);
}

t_hist		*entry_is_incomplete(t_pos *pos, t_hist *hist, char *buf)
{
	pos->act_co = pos->len_prompt;
	prepare_to_print(pos, buf);
	pos->let_nb_saved = ft_strlen(pos->ans);
	pos->was_incomplete = 1;
	return (hist);
}

t_hist		*entry_is_complete(t_pos *pos, t_hist *hist)
{
	while (hist->next)
		hist = hist->next;
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	if (ft_strlen(pos->ans) == 0)
		return (hist);
	if ((hist->prev && ft_strcmp(pos->ans, hist->prev->cmd) == 0))
	{
		ft_strdel(&hist->cmd);
		return (hist->prev);
	}
	write(pos->history, pos->ans, ft_strlen(pos->ans));
	write(pos->history, "\n", 1);
	while (hist->next)
		hist = hist->next;
	if (hist->cmd)
		ft_strdel(&hist->cmd);
	hist->cmd = ft_strdup(pos->ans);
	hist = add_list_back_hist(hist);
	hist = hist->prev;
	return (hist);
}

t_hist		*input_is_entry(t_pos *pos, t_hist *hist, char *buf)
{
	int		get_len;

	pos->is_complete = find_missing_quote(pos->ans);
	if (pos->is_complete == 0)
	{
		pos->history_mode = 0;
		input_is_printable_char(pos, buf);
	}
	get_len = get_len_with_lines(pos);
	pos->act_li = pos->start_li + get_len / pos->max_co;
	pos->act_co = get_len % pos->max_co;
	while (pos->act_li > pos->max_li)
	{
		pos->act_li -= 1;
		prompt_is_on_last_char(pos);
	}
	if (pos->is_complete == 0)
		entry_is_incomplete(pos, hist, buf);
	else
	{
		entry_is_complete(pos, hist);
		pos->was_incomplete = 0;
	}
	return (hist);
}
