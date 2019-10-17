/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 07:45:36 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 12:45:25 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf_err.h"

char				*fill_string_output_err(char *format, char *output, int i)
{
	int				j;
	int				k;
	int				initial_i;
	char			*tmp;

	j = -1;
	initial_i = i;
	k = i;
	while (format[i] && format[i] != '%')
		i++;
	tmp = ft_strnew(i - k);
	while (++j < i - initial_i)
		tmp[j] = format[k++];
	tmp[j] = '\0';
	output = free_strjoin(output, tmp);
	free(tmp);
	return (output);
}

int					is_contained_in_err(char *format, char *compare, int i)
{
	int				j;
	int				res;

	j = 0;
	res = 0;
	while (compare[j])
	{
		if (format[i] == compare[j])
			res++;
		j++;
	}
	return (res);
}

int					count_all_datas_err(char *format, int i)
{
	t_lengtherr		length;

	length.flags = "0+- #";
	length.nb = "0123456789";
	length.length = "hlL";
	length.conv = "cspfdiouxXb%TtW";
	while (is_contained_in_err(format, length.flags, i) > 0)
		i++;
	while (is_contained_in_err(format, length.nb, i) > 0)
		i++;
	if (format[i] == '.')
		i++;
	while (is_contained_in_err(format, length.nb, i) > 0)
		i++;
	while (is_contained_in_err(format, length.length, i) > 0)
		i++;
	if (is_contained_in_err(format, length.conv, i) > 0)
		i++;
	return (i);
}

int					crossing_pourcent_err(char *format, t_dataerr *data, int i,
					va_list va)
{
	data->output = fill_string_output_err((char*)format, data->output, i);
	while (format[i] && format[i] != '%')
		i++;
	if (format[i] == '%')
	{
		if (format[i + 1] != '\0')
		{
			data->output = determ_data_err((char*)format, data, va, ++i);
			i = count_all_datas_err((char*)format, i);
		}
		else
			i++;
	}
	return (i);
}

int					ft_printf_err(const char *format, ...)
{
	va_list			va;
	int				i;
	t_dataerr		data;
	int				final_len;

	data.backslash = 0;
	data.args_nb = 0;
	i = -1;
	while (format[++i])
	{
		if (format[i] == '%')
			data.args_nb++;
	}
	data.tab_arg_nb = init_tab_arg_nb_err(data);
	i = 0;
	data.output = ft_strnew(0);
	va_start(va, format);
	while (format[i])
		i = crossing_pourcent_err((char*)format, &data, i, va);
	va_end(va);
	final_len = print_printf_err(&data, 0);
	free_data_err(&data, 1);
	return (final_len);
}
