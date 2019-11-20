/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 07:45:36 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 14:16:18 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int					ft_printf_err_fd(const char *format, ...)
{
	va_list			va;
	int				i;
	t_dataerr		data;
	int				final_len;
	t_pos			*pos;

	pos = to_stock(NULL, 1);
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
	final_len = print_printf_err_fd(&data, 0, pos->act_fd_error);
	free_data_err(&data, 1);
	return (final_len);
}
