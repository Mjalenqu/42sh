/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bonus_conversion_type_3.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/04 13:13:25 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/04 14:59:52 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <ft_printf.h>

char			*upper_w_conv_2(t_tab *t, t_data *data)
{
	t->j = -1;
	while (t->tab[++t->j])
	{
		t->i = -1;
		while (t->tab[t->j][++t->i])
		{
			t->res = free_strjoin(t->res, t->tab[t->j][t->i]);
			t->length = 1;
			if (data->width > 0)
				t->length = data->width;
			while (--t->length >= 0 && t->tab[t->j][t->i + 1])
				t->res = free_strjoin(t->res, " ");
		}
		t->res = free_strjoin(t->res, "\n");
		if (data->prec_dot == 1 && data->prec > 0 && t->tab[t->j + 1])
		{
			t->width = data->prec;
			while (t->width-- > 0)
				t->res = free_strjoin(t->res, "\n");
		}
	}
	return (t->res);
}

char			*upper_w_conv(va_list va, t_data *data)
{
	t_tab		t;

	t.len = 0;
	t.tab = va_arg(va, char***);
	t.j = -1;
	t.res = ft_strnew(0);
	return (upper_w_conv_2(&t, data));
}
