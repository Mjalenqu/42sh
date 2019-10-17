/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_flags.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/11 13:57:58 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/01 06:52:22 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void			add_symb_diez(t_data *data, char **arg)
{
	if (data->conv_type == 6 && ft_strcmp(*arg, "0") != 0 &&
			ft_strcmp(*arg, "") != 0)
		*arg = add_char_begin_string(*arg, "0");
	if (data->conv_type == 8 && ft_strcmp(*arg, "0") != 0 &&
			ft_strcmp(*arg, "") != 0)
		*arg = add_char_begin_string(*arg, "0x");
	if (data->conv_type == 9 && ft_strcmp(*arg, "0") != 0 &&
			ft_strcmp(*arg, "") != 0)
		*arg = add_char_begin_string(*arg, "0X");
}

char			*flag_diez(t_data *data, char *arg)
{
	int			i;

	i = 0;
	if (data->conv_type == 3)
	{
		while (arg[i] && arg[i] != '.')
			i++;
		if (arg[i] == '\0')
			arg = add_char_end_string(arg, ".", 0);
	}
	else if ((data->conv_type == 6 && data->tmp_prec[0] == '\0') ||
			data->conv_type == 8 || data->conv_type == 9)
	{
		if (is_contained_in("0", data->flag, 0) == 1)
		{
			data->zero++;
			data->diez_length = 2;
			if (data->conv_type == 6)
				data->diez_length = 1;
			arg = flag_zero(*data, arg);
		}
		add_symb_diez(data, &arg);
	}
	data->diez_length = 1;
	return (arg);
}

char			*flag_space(t_data data, char *arg)
{
	int			i;
	int			find_zero;

	find_zero = -1;
	if (data.zero == 0)
	{
		while (data.flag[++find_zero])
		{
			if (data.flag[find_zero] == '0')
			{
				arg = flag_zero(data, arg);
				data.zero++;
			}
		}
	}
	i = -1;
	while (data.flag[++i])
	{
		if (data.flag[i] == '+')
			return (arg);
	}
	if (arg[0] != '-')
		arg = add_char_begin_string(arg, " ");
	return (arg);
}

char			*add_flag_to_conv(t_data data, char *arg, int i)
{
	data.plus = 0;
	data.space = 0;
	data.zero = 0;
	arg = handle_prec(data, arg);
	while (data.flag[++i] && (ft_strlen(arg) >= 1 || data.args_nb > 0))
	{
		if (data.flag[i] == '0' && data.zero == 0 && data.conv_type != 10)
			arg = flag_zero(data, arg);
		if (data.flag[i] == '+' && data.plus++ == 0 && data.conv_type != 10)
		{
			if (arg[0] != '-' && data.conv_type >= 3 && data.conv_type <= 5 &&
					data.f_nan != 1)
				arg = add_char_begin_string(arg, "+");
		}
		else if (data.flag[i] == '-' && data.width != 0)
			arg = flag_minus(data, arg, -1);
		else if (data.flag[i] == '#' && data.conv_type != 10)
			arg = flag_diez(&data, arg);
		if (data.flag[i] == ' ' && ((data.conv_type >= 3 &&
			data.conv_type <= 5) || data.conv_type == 10) && data.space++ == 0)
			arg = flag_space(data, arg);
	}
	arg = handle_width(data, arg);
	return (arg);
}
