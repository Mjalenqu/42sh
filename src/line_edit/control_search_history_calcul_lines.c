/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   control_search_history_calcul_pos.c              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 07:22:34 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 14:30:56 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		get_pos_coordinates_right_again(t_pos *pos)
{
	int		i;

	i = 0;
	pos->act_li = pos->start_li;
	pos->act_co = pos->len_prompt;
	while (pos->ans[i])
	{
		if (pos->ans[i] == '\n' || pos->act_co == pos->max_co - 1)
		{
			pos->act_li += 1;
			pos->act_co = 0;
		}
		else
			pos->act_co += 1;
		i++;
	}
}

void		count_ctrl_col_and_line(t_pos *pos, char *ans, t_ctrl_hist *ctrl,
			int needle)
{
	int		i;

	i = 0;
	while (ans[i] && i < needle)
	{
		if (ans[i] == '\n' || ctrl->act_co == pos->max_co - 1)
		{
			ctrl->act_li++;
			ctrl->act_co = 0;
		}
		else
			ctrl->act_co++;
		i++;
	}
}

int			count_cmd_line_len(t_pos *pos, char *ans, int act_co)
{
	int		nb_line;
	int		i;

	i = 0;
	nb_line = 0;
	while (ans[i])
	{
		if (ans[i] == '\n' || act_co == pos->max_co - 1)
		{
			nb_line++;
			act_co = 0;
		}
		else
			act_co++;
		i++;
	}
	return (nb_line);
}

t_hist		*exit_control_search(t_hist *hist, t_pos *pos)
{
	hist = exiting_control_mode(pos, hist);
	while (hist->next)
		hist = hist->next;
	if (pos->ans && ft_strlen(pos->ans) > 0)
	{
		hist->cmd = ft_strdup(pos->ans);
		hist->next = add_list_back_hist(hist);
	}
	ft_strdel(&pos->saved_ans);
	return (hist);
}
