/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_printf.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 14:54:19 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 12:45:52 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf_err.h"

int		check_if_color_err(t_dataerr *d, int i)
{
	t_colorerr col;

	init_color_printf_err(&col);
	while (d->output[i] && d->output[i] != '}')
	{
		if (check_color_code_err(d, &col, i, 0) > 0)
		{
			i += 2;
			while (((d->output[i] < 'A' || d->output[i] > 'Z') &&
				d->output[i] != '}' && (col.back != -1 || col.text != -1)))
				i++;
		}
		else if (ft_strncmp(d->output + i, "eoc}", 4) == 0)
			return (1);
		else
			return (0);
	}
	return (1);
}

int		iterating_through_output_err(t_dataerr *data, int *printed_backslash,
		int i)
{
	if (data->output[i] && data->output[i] == '{' &&
		check_if_color_err(data, i + 1))
	{
		i = handle_colors_err(data, i + 1, i + 1);
		if (data->output[i] == '}')
			return (i + 1);
	}
	if (data->backslash > 0 && *printed_backslash <= data->backslash &&
			*printed_backslash < data->args_nb &&
			i == data->tab_arg_nb[*printed_backslash])
	{
		*printed_backslash += 1;
		ft_putchar_fd('\0', 2);
	}
	if (data->output[i] && data->output[i] == '\n' && data->last_color != NULL)
	{
		ft_putstr_fd("\033[0m\n", 2);
		ft_putstr_fd(data->last_color, 2);
		i++;
	}
	else if (data->output[i])
		ft_putchar_fd(data->output[i++], 2);
	return (i);
}

int		print_printf_err(t_dataerr *data, int i)
{
	int	printed_backslash;
	int	backslash_last_pos;

	printed_backslash = 0;
	backslash_last_pos = 0;
	data->code = NULL;
	data->last_color = NULL;
	while (data->output[i])
		i = iterating_through_output_err(data, &printed_backslash, i);
	if (printed_backslash < data->args_nb &&
		data->tab_arg_nb[printed_backslash] == (int)ft_strlen(data->output) &&
		data->backslash > 0)
	{
		ft_putchar_fd('\0', 2);
		backslash_last_pos++;
	}
	if (data->last_color != NULL)
	{
		ft_putstr_fd("\033[0m", 2);
		free(data->last_color);
	}
	return (i + printed_backslash + backslash_last_pos);
}
