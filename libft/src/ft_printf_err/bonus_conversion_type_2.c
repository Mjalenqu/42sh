/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bonus_conversion_type_2.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/01 07:16:02 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 11:14:06 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf_err.h"

void		init_tab_err(t_taberr *t)
{
	t->init_tab = NULL;
	t->tab = NULL;
	t->int_tab = NULL;
	t->res = NULL;
	t->i = 0;
	t->j = 0;
	t->k = 0;
	t->flag_space = 0;
	t->len = 0;
	t->diff = 0;
	t->length = 0;
	t->width = 0;
}

void		t_conv_3_err(t_taberr *tab, t_dataerr *data)
{
	int		nb_size;
	char	*tmp;

	nb_size = tab->biggest - check_num_length(tab->int_tab[tab->j][tab->i]);
	if (tab->int_tab[tab->j][tab->i] < 0)
		nb_size--;
	if (tab->i == 0)
		nb_size--;
	while (nb_size-- >= 0)
		tab->res = free_strjoin(tab->res, " ");
	tmp = ft_itoa(tab->int_tab[tab->j][tab->i]);
	tab->res = free_strjoin(tab->res, tmp);
	tab->flag_space = data->width + 1;
	while (--tab->flag_space > 0 && tab->i + 1 < tab->length)
		tab->res = free_strjoin(tab->res, " ");
	free(tmp);
}

char		*t_conv_2_err(t_taberr tab, t_dataerr *data)
{
	tab.j = -1;
	while (++tab.j < tab.width)
	{
		tab.i = -1;
		while (++tab.i < tab.length)
			t_conv_3_err(&tab, data);
		if (tab.j + 1 < tab.width)
		{
			if (data->prec_dot == 1)
			{
				tab.flag_space = data->prec + 1;
				while (--tab.flag_space >= 0)
					tab.res = free_strjoin(tab.res, "\n");
			}
			else
				tab.res = free_strjoin(tab.res, "\n");
		}
	}
	return (tab.res);
}

char		*t_conv_err(va_list va, t_dataerr *data)
{
	t_taberr	tab;

	init_tab_err(&tab);
	tab.int_tab = va_arg(va, int**);
	tab.width = va_arg(va, int);
	tab.length = va_arg(va, int);
	tab.j = -1;
	tab.biggest = 0;
	while (++tab.j < tab.width)
	{
		tab.i = -1;
		while (++tab.i < tab.length)
		{
			tab.diff = check_num_length(tab.int_tab[tab.j][tab.i]);
			if (tab.int_tab[tab.j][tab.i] < 0)
				tab.diff++;
			if (tab.diff > tab.biggest)
				tab.biggest = tab.diff;
		}
	}
	tab.j = -1;
	tab.res = ft_strnew(0);
	return (t_conv_2_err(tab, data));
}
