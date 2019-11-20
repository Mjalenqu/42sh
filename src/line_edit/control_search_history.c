/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   control_search_history.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/15 13:30:27 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 12:41:13 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int			get_pos_strstr(char *str, char *tofind, int i, int j)
{
	if (str == NULL || tofind == NULL)
		return (-1);
	while (str[i] && i + ft_strlen(tofind) <= ft_strlen(str))
	{
		if (str[i] != tofind[j])
			i++;
		else
		{
			while (str[i] && tofind[j] && str[i] == tofind[j])
			{
				i++;
				j++;
			}
			if (j == ft_strlen(tofind))
				return (i - j);
			else
			{
				i = i - j + 1;
				j = 0;
			}
		}
	}
	return (-1);
}

t_hist		*exiting_control_mode(t_pos *pos, t_hist *hist)
{
	pos->ctrl_search_history = 0;
	if (pos->ctrl_hist_cmd && ft_strlen(pos->ctrl_hist_cmd) > 0)
	{
		pos->ans = ft_secure_free(pos->ans);
		pos->ans = ft_strnew(ft_strlen(pos->ctrl_hist_cmd));
		pos->ans = ft_strcpy(pos->ans, pos->ctrl_hist_cmd);
		clean_at_start(pos);
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, pos->start_li), 1, ft_putchar);
	print_prompt(pos);
	write(1, pos->ans, ft_strlen(pos->ans));
	pos->ctrl_search_history = 0;
	pos->history_mode = 0;
	get_pos_coordinates_right_again(pos);
	if (ft_strlen(pos->ctrl_hist_cmd) == 0)
	{
		pos->ans = ft_secure_free(pos->ans);
		pos->ans = ft_strnew(0);
		pos->act_co = pos->len_prompt;
		pos->act_li = pos->start_li;
		hist->cmd = ft_secure_free(hist->cmd);
	}
	pos->let_nb = ft_strlen(pos->ans);
	pos->ctrl_hist_cmd = ft_secure_free(pos->ctrl_hist_cmd);
	return (hist);
}

void		needle_found_in_history(t_pos *pos, t_hist *hist, t_ctrl_hist *ctrl)
{
	write(1, hist->cmd, ft_strlen(hist->cmd));
	get_right_coordinates_found(pos, hist, ctrl);
	ctrl->act_li = pos->start_li;
	count_ctrl_col_and_line(pos, hist->cmd, ctrl, ctrl->needle);
	if (ctrl->act_li > pos->start_li)
		ctrl->act_co -= 1;
	ctrl->act_li += count_cmd_line_len(pos, pos->ans, pos->len_prompt + 19);
	if (ctrl->act_li > pos->max_co)
		ctrl->act_li = ctrl->act_li - (ctrl->act_li - pos->max_co);
	if (pos->ctrl_hist_cmd)
		pos->ctrl_hist_cmd = ft_secure_free(pos->ctrl_hist_cmd);
	pos->ctrl_hist_cmd = ft_strnew(ft_strlen(hist->cmd));
	ft_strcpy(pos->ctrl_hist_cmd, hist->cmd);
}

t_hist		*search_occurence_in_history(t_pos *pos, t_hist *hist,
			t_ctrl_hist *ctrl)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (hist->prev != NULL && ctrl->needle == -1)
	{
		if (hist->prev)
			hist = hist->prev;
		ctrl->needle = get_pos_strstr(hist->cmd, pos->ans, i, j);
		if (ctrl->needle >= 0)
			needle_found_in_history(pos, hist, ctrl);
	}
	if (ctrl->needle == -1)
	{
		get_right_coordinates_not_found(pos, ctrl);
		pos->ctrl_hist_cmd = ft_secure_free(pos->ctrl_hist_cmd);
		pos->ctrl_hist_cmd = ft_strnew(0);
		while (hist->next)
			hist = hist->next;
	}
	return (hist);
}

t_hist		*control_search_history(t_pos *pos, t_hist *hist,
			unsigned char *buf)
{
	t_ctrl_hist	ctrl;

	ctrl.needle = -1;
	pos->ctrl_search_history = 1;
	pos->ans_printed = 1;
	ctrl.act_li = pos->start_li;
	ctrl.act_co = pos->act_co;
	pos->let_nb = ft_strlen(pos->ans);
	if (buf[0] == 10 && (buf[0] = 0) == 0)
		return (exit_control_search(hist, pos));
	clean_at_start(pos);
	ft_printf("(reverse-i-search)`%s': ", pos->ans);
	while (hist->next)
		hist = hist->next;
	hist = search_occurence_in_history(pos, hist, &ctrl);
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
	return (hist);
}
