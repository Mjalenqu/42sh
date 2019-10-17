/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   control_search_history_calcul_pos.c              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/27 13:40:12 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/02 12:24:10 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static void	calcul_len_of_ctrl_prompt(t_pos *pos, t_ctrl_hist *ctrl)
{
	int		check_new_line;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(pos->ans);
	check_new_line = 0;
	while (i < 22 + len + check_new_line)
	{
		if (ctrl->act_co == pos->max_co - 1 ||
			(i >= 21 && i - 21 < ft_strlen(pos->ans) &&
			pos->ans[i - 21] == '\n'))
		{
			ctrl->act_co = 0;
			ctrl->act_li += 1;
			if ((i >= 21 && pos->ans[i - 21] == '\n'))
				check_new_line = 2;
		}
		else
			ctrl->act_co += 1;
		i += 1;
	}
}

void		get_right_coordinates_not_found(t_pos *pos, t_ctrl_hist *ctrl)
{
	ctrl->act_co = pos->len_prompt;
	if (ft_strlen(pos->ans) + 24 == pos->max_co && ctrl->needle == -1 &&
			pos->act_li == pos->max_li)
		prompt_is_on_last_char(pos);
	ctrl->act_li = pos->start_li;
	calcul_len_of_ctrl_prompt(pos, ctrl);
	while (ctrl->act_li > pos->max_li)
	{
		ctrl->act_li -= 1;
		pos->start_li -= 1;
	}
	pos->act_co = ctrl->act_co;
	pos->act_li = ctrl->act_li;
}

void		get_right_coordinates_found(t_pos *pos, t_hist *hist,
		t_ctrl_hist *ctrl)
{
	int		nb_line_lost;

	nb_line_lost = 0;
	get_right_coordinates_not_found(pos, ctrl);
	count_ctrl_col_and_line(pos, hist->cmd, ctrl, ft_strlen(hist->cmd));
	while (ctrl->act_li > pos->max_li)
	{
		ctrl->act_li -= 1;
		pos->start_li -= 1;
		nb_line_lost += 1;
	}
	ctrl->act_co = pos->act_co;
	ctrl->act_li = pos->act_li - nb_line_lost;
	count_ctrl_col_and_line(pos, hist->cmd, ctrl, ctrl->needle);
	pos->act_co = ctrl->act_co;
	pos->act_li = ctrl->act_li;
}
