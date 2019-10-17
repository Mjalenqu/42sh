/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute_fc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 18:30:58 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/06 13:08:20 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static void		print_l_flag(t_fc *fc, t_hist *hist)
{
	if (fc->int_first <= fc->int_last)
	{
		while (fc->int_first <= fc->int_last && hist->next->next)
		{
			if (ft_strchr(fc->flags, 'n') == NULL)
				ft_printf("%d", hist->cmd_no + 1);
			ft_printf("	%s\n", hist->cmd);
			fc->int_first += 1;
			hist = hist->next;
		}
	}
	else if (fc->int_first > fc->int_last)
	{
		while (fc->int_first >= fc->int_last && hist)
		{
			if (ft_strchr(fc->flags, 'n') == NULL)
				ft_printf("%d", hist->cmd_no + 1);
			ft_printf("	%s\n", hist->cmd);
			fc->int_first -= 1;
			hist = hist->prev;
			if (fc->int_first == fc->int_last && (fc->int_first < 0 ||
						fc->int_last < 0))
				break ;
		}
	}
}

static void		correct_int_first_and_int_last(t_fc *fc, t_hist *hist)
{
	if (fc->int_first >= hist->cmd_no)
		fc->int_first = hist->cmd_no - 1;
	if (fc->int_last >= hist->cmd_no)
		fc->int_last = hist->cmd_no - 1;
	if (fc->first_not_precised == 1 && fc->last_not_precised == 1)
	{
		fc->int_first = hist->cmd_no - 15;
		if (fc->int_first < 0)
			fc->int_first = 0;
		fc->int_last = hist->cmd_no - 1;
	}
	else if (fc->first_not_precised == 1)
		fc->int_first = hist->cmd_no;
	else if (fc->last_not_precised == 1)
		fc->int_last = hist->cmd_no;
	if (fc->int_first < 0)
	{
		fc->int_first = (hist->cmd_no + fc->int_first);
		fc->first_not_precised = 2;
	}
	if (fc->int_last < 0)
	{
		fc->int_last = (hist->cmd_no + fc->int_last);
		fc->last_not_precised = 2;
	}
}

void			inverse_first_and_last_if_flag_r(t_fc *fc)
{
	int			swap;

	swap = fc->int_first;
	fc->int_first = fc->int_last;
	fc->int_last = swap;
	swap = fc->first_is_str;
	fc->first_is_str = fc->last_is_str;
	fc->last_is_str = swap;
}

void			prepare_l_flag(t_fc *fc, t_hist *hist)
{
	correct_int_first_and_int_last(fc, hist);
	if (ft_strchr(fc->flags, 'r') != NULL)
		inverse_first_and_last_if_flag_r(fc);
	while (hist->prev && hist->cmd_no + 1 > fc->int_first)
		hist = hist->prev;
	print_l_flag(fc, hist);
}
