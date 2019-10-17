/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bonus_conversion_type_1.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 13:49:55 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/27 09:26:52 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf_err.h"

char		*split_binary_err(char *num, int i)
{
	int		j;
	char	*res;
	int		nb_bits;

	nb_bits = -2;
	i = ft_strlen(num);
	j = i;
	while (j % 4 != 0)
		j++;
	j += j / 4 - 1;
	res = ft_strnew(j);
	while (j >= 0 && ++nb_bits >= -2)
	{
		if ((j - 4) % 5 == 0 && (nb_bits - 4) % 5 == 0 && nb_bits > 0)
			res[j--] = ' ';
		else if (i >= 0)
			res[j--] = num[i--];
		else
			res[j--] = '0';
	}
	free(num);
	return (res);
}

char		*flag_binary_err(t_dataerr *data, char *num,
			int i, unsigned long long nb)
{
	if (data->flag[i] == '\0' && nb == 0 && data->prec_dot == 1
			&& data->prec == 0)
	{
		num[0] = '\0';
		data->backslash++;
	}
	if (is_contained_in_err("#", data->flag, 0) == 1)
		num = split_binary_err(num, 0);
	return (num);
}

char		*b_conv_err(va_list va, t_dataerr *data)
{
	unsigned long long	nb;
	char				*num;
	int					i;

	i = 0;
	nb = 0;
	if (data->length[0] == '\0')
		nb = va_arg(va, unsigned int);
	else if (ft_strcmp(data->length, "hh") == 0)
		nb = (unsigned char)va_arg(va, long long);
	else if (ft_strcmp(data->length, "h") == 0)
		nb = (unsigned short)va_arg(va, long long);
	else if (ft_strcmp(data->length, "l") == 0)
		nb = va_arg(va, unsigned long);
	else if (ft_strcmp(data->length, "ll") == 0)
		nb = va_arg(va, unsigned long long);
	while (data->flag[i] && data->flag[i] != '#')
		i++;
	num = ft_itoa_base_uns((unsigned long long)nb, 2);
	return (flag_binary_err(data, num, i, nb));
}

char		*upper_t_conv_2_err(t_taberr tab, t_dataerr *data)
{
	tab.k = 0;
	tab.j = -1;
	while (tab.init_tab[++tab.j])
	{
		tab.i = 0;
		while (tab.init_tab[tab.j][tab.i])
		{
			tab.res[tab.k++] = tab.init_tab[tab.j][tab.i++];
			tab.flag_space = data->width + 1;
			while (--tab.flag_space > 0 && tab.init_tab[tab.j][tab.i])
				tab.res[tab.k++] = ' ';
		}
		if (tab.init_tab[tab.j + 1])
		{
			if (data->prec_dot == 1)
			{
				tab.flag_space = data->prec + 1;
				while (--tab.flag_space >= 0)
					tab.res[tab.k++] = '\n';
			}
			else
				tab.res[tab.k++] = '\n';
		}
	}
	return (tab.res);
}

char		*upper_t_conv_err(va_list va, t_dataerr *data)
{
	t_taberr	tab;

	tab.init_tab = va_arg(va, char**);
	tab.i = -1;
	tab.len = 0;
	while (tab.init_tab[++tab.i])
		tab.len += (data->width + 1) * ft_strlen(tab.init_tab[tab.i]) + 1;
	tab.len--;
	if (data->prec_dot == 1)
		tab.len += data->prec * (tab.i - 1);
	tab.res = ft_strnew(tab.len);
	return (upper_t_conv_2_err(tab, data));
}
