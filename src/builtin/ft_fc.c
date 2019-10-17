/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fc.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 11:18:28 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 15:51:31 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

static void		init_fc_struct(t_fc *fc)
{
	fc->flags_model = ft_strdup("elnrs");
	fc->flags = ft_strnew(6);
	fc->ename = NULL;
	fc->str_first = NULL;
	fc->str_last = NULL;
	fc->int_first = -1;
	fc->int_last = -1;
	fc->first_is_str = -1;
	fc->last_is_str = -1;
	fc->first_not_precised = -1;
	fc->last_not_precised = -1;
	fc->error = 0;
}

void			induced_e_flag_check_first_arg(t_fc *fc, t_process *p)
{
	if (p->cmd[1] && ((p->cmd[1][0] > '0' && p->cmd[1][0] <= '9') ||
		(p->cmd[1][1] && p->cmd[1][0] == '-' && p->cmd[1][1] > '0' &&
		p->cmd[1][1] <= '9')))
	{
		fc->first_not_precised = 0;
		fc->int_first = ft_atoi(p->cmd[1]);
	}
	else if (p->cmd[1])
	{
		fc->first_not_precised = 0;
		fc->str_first = ft_strdup(p->cmd[1]);
	}
}

void			check_if_e_flag_induced(t_fc *fc, t_process *p, t_hist *hist)
{
	induced_e_flag_check_first_arg(fc, p);
	if (p->cmd[1] && p->cmd[2] && ((p->cmd[2][0] > '0' && p->cmd[2][0] <= '9')
		|| (p->cmd[2][1] && p->cmd[2][0] == '-' && p->cmd[2][1] > '0' &&
		p->cmd[2][1] <= '9')))
	{
		fc->last_not_precised = 0;
		fc->int_last = ft_atoi(p->cmd[2]);
	}
	else if (p->cmd[1] && p->cmd[2])
	{
		fc->last_not_precised = 0;
		fc->str_last = ft_strdup(p->cmd[2]);
	}
	else if (!p->cmd[1])
	{
		fc->first_not_precised = 0;
		fc->int_first = hist->cmd_no - 1;
	}
}

static void		execute_fc_according_to_flags(t_fc *fc, t_var **var,
				t_process *p)
{
	t_hist		*hist;
	int			i;

	i = 0;
	hist = stock(NULL, 8);
	while (hist && hist->next)
		hist = hist->next;
	if (ft_strlen(fc->flags) == 0)
		check_if_e_flag_induced(fc, p, hist);
	if (fc->int_first == 0 && fc->first_is_str == -1)
		fc->int_first = hist->cmd_no - 1;
	if (fc->int_last == 0 && fc->last_is_str == -1)
		fc->int_last = hist->cmd_no - 1;
	if (fc->error == 1)
	{
		free_fc_struct(fc);
		return ;
	}
	if (ft_strchr(fc->flags, 'l') != NULL)
		prepare_l_flag(fc, hist);
	else if (ft_strchr(fc->flags, 's') != NULL)
		prepare_s_flag(fc, hist, var);
	else if (ft_strchr(fc->flags, 'e') != NULL || ft_strlen(fc->flags) == 0)
		prepare_e_flag(fc, hist, var, i);
}

int				ft_fc(t_process *p, t_var **var)
{
	t_fc	fc;
	int		i;

	init_fc_struct(&fc);
	i = determ_fc_flags(&fc, p, 0, 1);
	if (p->cmd[i] && ft_strcmp(p->cmd[i], "--") == 0)
		i += 1;
	if (fc.error == 0)
	{
		get_str_args_of_fc(&fc, p, i, 0);
		if (fc.error == 0)
			execute_fc_according_to_flags(&fc, var, p);
	}
	free_fc_struct(&fc);
	if (fc.error == 0)
		return (0);
	return (1);
}
