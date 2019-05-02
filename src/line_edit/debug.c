/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/30 09:27:30 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 10:39:57 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void	clear_info()
{
	int 	i;

	i = 0;
	while (i < 21)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, i), 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		i++;
	}
	i = -1;
	while (++i < tgetnum("co"))
		write(1, "-", 1);
}

void	print_info(t_pos *pos)
{
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	clear_info();
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 0), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}act_co    = %03d/{eoc}\n", pos->act_co);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 1), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}act_li    = %03d/{eoc}\n", pos->act_li);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 2), 1, ft_putchar);	
	ft_printf(" {S.white.T.grey.}start_co  = %03d/{eoc}\n", pos->start_co);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 3), 1, ft_putchar);	
	ft_printf(" {S.white.T.grey.}start_li  = %03d/{eoc}\n", pos->start_li);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 4), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}max_co    = %03d/{eoc}\n", pos->max_co);	
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 5), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}max_li    = %03d/{eoc}\n", pos->max_li);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 6), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}let_nb    = %03d/{eoc}\n", pos->let_nb);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 7), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}let_nb_sav= %03d/{eoc}\n", pos->let_nb_saved);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 8), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}strlen_ans= %03d/{eoc}\n", ft_strlen(pos->ans));
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 9), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}len_ans   = %03d/{eoc}\n", pos->len_ans);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 10), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}historyMd = %03d/{eoc}\n", pos->history_mode);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 11), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}len_prompt= %03d/{eoc}\n", pos->len_prompt);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 12), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}is_compl  = %03d/{eoc}\n", pos->is_complete);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 13), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}histloop  = %03d/{eoc}\n", pos->history_loop);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 14), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}debug     = %03d/{eoc}\n", pos->debug);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 15), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}debug2    = %03d/{eoc}\n", pos->debug2);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 16), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}debug3    = %03d/{eoc}\n", pos->debug3);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 17), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}debug4    = %03d/{eoc}\n", pos->debug4);
	tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 17, 18), 1, ft_putchar);
	ft_printf(" {S.white.T.grey.}debug5    = %03d/{eoc}\n", pos->debug5);
	//	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar);
	//	ft_printf(" {S.white.T.grey.}pos->ans  = %-140.140s/{eoc}\n", pos->ans);
/*	if (pos->saved_ans != NULL)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, 3), 1, ft_putchar);
		ft_printf(" {S.white.T.grey.}pos->saved_ans = %-20.20s/{eoc}\n", pos->saved_ans);
	}
*/	/*		tputs(tgoto(tgetstr("cm", NULL), 0, 4), 1, ft_putchar);
			ft_printf(" {S.white.T.grey.}pos->saved_ans = %-d/{eoc}\n", pos->saved_ans == NULL ? -1 : pos->saved_ans[0]);
			}*/
tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

void	print_hist(t_pos *pos, t_hist *hist)
{
	t_hist	*tmp;
	int		i;
	int		actual_hist;

	if (hist == NULL)
		return;
	tmp = hist;
	actual_hist = tmp->cmd_no;
	i = 0;
	while (tmp->prev)
		tmp = tmp->prev;
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	while (tmp)
	{
		if (i == 20)
			break ;
		tputs(tgoto(tgetstr("cm", NULL), pos->max_co - 77, i), 1, ft_putchar);
		if (actual_hist == tmp->cmd_no)
			ft_printf(" {S.white.T.grey.}cmd[%3d]    = {S.red.T.white.}%-35.35s{S.white.T.grey.}/{eoc}\n", i, tmp == NULL ? NULL : tmp->cmd);
		else
			ft_printf(" {S.white.T.grey.}cmd[%3d]    = %-35.35s/{eoc}\n", i, tmp == NULL ? NULL : tmp->cmd);
		i++;
		tmp = tmp->next;
	}
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

