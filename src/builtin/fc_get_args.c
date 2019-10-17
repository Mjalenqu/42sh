/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_get_args.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 18:16:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 07:57:56 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void			make_str_last_into_int(t_fc *fc, t_hist *hist)
{
	while (hist && hist->next && hist->next->next)
		hist = hist->next;
	if (fc->last_is_str == 1)
	{
		while (hist->prev)
		{
			hist = hist->prev;
			if (ft_strncmp(fc->str_last, hist->cmd,
						ft_strlen(fc->str_last)) == 0)
			{
				fc->int_last = hist->cmd_no + 1;
				break ;
			}
		}
	}
}

void			make_str_arg_into_int(t_fc *fc, t_hist *hist)
{
	if (fc->first_is_str == 1)
	{
		while (hist->prev)
		{
			hist = hist->prev;
			if (ft_strncmp(fc->str_first, hist->cmd,
						ft_strlen(fc->str_first)) == 0)
			{
				fc->int_first = hist->cmd_no + 1;
				break ;
			}
		}
	}
	make_str_last_into_int(fc, hist);
	if ((fc->int_first == -1 || fc->int_last == -1) && fc->error++ == 0)
		ft_printf_err("%s: fc: history specification out of range\n", TERM);
}

static void		check_if_str_args_need_correction(t_fc *fc, int check)
{
	if (check == 0)
	{
		if (fc->first_is_str == -1)
		{
			fc->first_not_precised = 1;
			fc->int_first = 0;
		}
		if (fc->last_is_str == -1)
		{
			fc->last_not_precised = 1;
			fc->int_last = 0;
		}
	}
	if (check == 1 && fc->last_is_str == -1)
	{
		fc->last_not_precised = 1;
		fc->int_last = 0;
	}
	if (fc->first_is_str == 1 || fc->last_is_str == 1)
		make_str_arg_into_int(fc, stock(NULL, 8));
}

void			circle_through_cmd_args(t_fc *fc, t_process *p, int i,
				int check)
{
	if (((p->cmd[i][0] >= '0' && p->cmd[i][0] <= '9') || (p->cmd[i][1]
	&& p->cmd[i][0] == '-' && p->cmd[i][1] >= '0' && p->cmd[i][1] <= '9'))
			&& check == 0)
	{
		fc->int_first = ft_atoi(p->cmd[i]);
		fc->first_is_str = 0;
	}
	else if (((p->cmd[i][0] >= '0' && p->cmd[i][0] <= '9') || (p->cmd[i][1]
	&& p->cmd[i][0] == '-' && p->cmd[i][1] >= '0' && p->cmd[i][1] <= '9'))
			&& check == 1)
	{
		fc->int_last = ft_atoi(p->cmd[i]);
		fc->last_is_str = 0;
	}
	else if (check == 0)
	{
		fc->str_first = ft_strdup(p->cmd[i]);
		fc->first_is_str = 1;
	}
	else if (check == 1)
	{
		fc->str_last = ft_strdup(p->cmd[i]);
		fc->last_is_str = 1;
	}
}

void			get_str_args_of_fc(t_fc *fc, t_process *p, int i, int check)
{
	if (p->cmd[i] && ft_strchr(fc->flags, 's') != NULL &&
			ft_strchr(p->cmd[i], '=') != NULL)
		fc->ename = ft_strdup(p->cmd[i++]);
	else if ((ft_strchr(fc->flags, 'e') != NULL && (p->cmd[i][0] < '0' ||
		p->cmd[i][0] > '9') && (p->cmd[i][1] < '0' || p->cmd[i][1] > '9')))
		fc->ename = ft_strdup(p->cmd[i++]);
	while (p->cmd[i] && check < 2)
	{
		circle_through_cmd_args(fc, p, i, check);
		i++;
		check++;
	}
	check_if_str_args_need_correction(fc, check);
}
