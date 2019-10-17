/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_is_entry.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 07:27:11 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 15:36:01 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static t_hist	*entry_is_incomplete(t_pos *pos, t_hist *hist, char *buf)
{
	pos->act_co = pos->len_prompt;
	prepare_to_print(pos, buf);
	pos->let_nb_saved = ft_strlen(pos->ans);
	pos->was_incomplete = 1;
	return (hist);
}

static void		write_in_history_file(t_pos *pos)
{
	if (pos->active_heredoc == 0)
		write(pos->history, pos->ans, ft_strlen(pos->ans));
	else
		write(pos->history, pos->ans_heredoc_save,
		ft_strlen(pos->ans_heredoc_save));
	write(pos->history, "\n", 1);
}

t_hist			*entry_is_complete(t_pos *pos, t_hist *hist)
{
	if (pos->is_expansion-- > 0)
		return (hist);
	while (hist && hist->next)
		hist = hist->next;
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	if (ft_strlen(pos->ans) == 0)
		return (hist);
	if ((hist && hist->prev && ft_strcmp(pos->ans, hist->prev->cmd) == 0))
	{
		hist->cmd = ft_secure_free(hist->cmd);
		return (hist->prev);
	}
	write_in_history_file(pos);
	while (hist->next)
		hist = hist->next;
	if (hist->cmd)
		hist->cmd = ft_secure_free(hist->cmd);
	hist->cmd = pos->active_heredoc == 0 ? ft_strdup(pos->ans) :
		ft_strdup(pos->ans_heredoc_save);
	hist = add_list_back_hist(hist);
	hist = hist->prev;
	pos->was_incomplete = 0;
	return (hist);
}

static void		check_expansion_and_token(t_pos *pos, t_hist *hist)
{
	int		i;

	i = ft_strlen(pos->ans);
	if (pos->active_heredoc == 0)
		pos->ans = check_backslash(pos);
	if (i != ft_strlen(pos->ans))
	{
		clean_at_start(pos);
		print_ans(pos, 0, pos->start_co);
		pos->ans_printed = 1;
	}
	check_history_expansion(pos, hist, -1, 0);
	pos->ctrl_hist_cmd = ft_secure_free(pos->ctrl_hist_cmd);
	if (pos->active_heredoc == 0)
		pos->is_complete = token(pos->ans, pos);
	if (ft_strchr(pos->ans, '<') != NULL && (pos->is_complete == 1 ||
		pos->active_heredoc == 1))
		check_for_heredoc(pos, 0, -1);
}

t_hist			*input_is_entry(t_pos *pos, t_hist *hist, char *buf)
{
	check_expansion_and_token(pos, hist);
	if (pos->ans == NULL)
	{
		ft_strdel(&pos->saved_ans);
		return (hist);
	}
	if (check_ans(pos->ans) == 1)
	{
		while (hist->next)
			hist = hist->next;
		hist->cmd = ft_secure_free(hist->cmd);
		return (hist);
	}
	if (pos->is_complete == 0)
	{
		pos->history_mode = 0;
		input_is_printable_char(pos, buf);
	}
	short_update(pos, get_len_with_lines(pos));
	if (pos->is_complete == 0)
		entry_is_incomplete(pos, hist, buf);
	else
		entry_is_complete(pos, hist);
	return (hist);
}
