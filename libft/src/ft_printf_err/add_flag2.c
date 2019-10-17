/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_flag2.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/31 11:49:44 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 12:44:28 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf_err.h"

char				*flag_zero_err(t_dataerr data, char *arg)
{
	int				i;
	size_t			tmp_plus;

	tmp_plus = 0;
	if (is_contained_in_err("+", data.flag, 0) == 1 && arg[0] != '-')
		tmp_plus++;
	i = 0;
	arg = handle_plus_minus_with_zero_err(data, arg);
	if (data.prec_dot == 0 || data.conv_type == 0 || data.conv_type == 3)
	{
		while (data.flag[i] && data.flag[i] != '-')
			i++;
	}
	if (data.flag[i] == '\0' && ft_strlen(arg) < data.width)
	{
		while ((unsigned long)ft_strlen(arg) < (data.width - tmp_plus -
				data.space) - data.minus - data.diez_length)
			arg = add_char_begin_string_err(arg, "0");
	}
	if (data.plus > 0)
		arg = add_char_begin_string_err(arg, "+");
	else if (data.minus > 0)
		arg = add_char_begin_string_err(arg, "-");
	return (arg);
}

char				*flag_minus_err(t_dataerr data, char *arg, int i)
{
	char			*right_width;
	char			*tmp;
	int				find_space;

	find_space = -1;
	while (data.flag[++find_space])
	{
		if (data.flag[find_space] == ' ' || (data.flag[find_space] == '+' &&
					data.f_nan != 1 && data.plus != 1 && data.f_inf != 1))
			data.width--;
	}
	right_width = ft_strnew(data.width);
	while (++i < (data.width - (int)ft_strlen(arg)))
	{
		if ((((is_contained_in_err("+", data.flag, 0) == 1) && data.f_inf == 1)
	|| (is_contained_in_err("#", data.flag, 0) == 1 && data.conv_type == 6 &&
	data.diez_length == 0)) && i == (data.width - (int)ft_strlen(arg) - 1))
			break ;
		right_width[i] = ' ';
	}
	tmp = arg;
	arg = ft_strjoin(arg, right_width);
	free(tmp);
	free(right_width);
	return (arg);
}
