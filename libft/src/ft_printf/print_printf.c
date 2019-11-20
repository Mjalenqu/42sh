/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_printf.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 14:54:19 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 12:56:32 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_if_color(t_data *d, int i)
{
	t_color col;

	init_color_printf(&col);
	while (d->output[i] && d->output[i] != '}')
	{
		if (check_color_code(d, &col, i, 0) > 0)
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

int		iterating_through_output(t_data *data, int *printed_backslash, int i)
{
	if (data->output[i] && data->output[i] == '{' &&
		check_if_color(data, i + 1))
	{
		i = handle_colors(data, i + 1, i + 1);
		if (data->output[i] == '}')
			return (i + 1);
	}
	if (data->backslash > 0 && *printed_backslash <= data->backslash &&
			*printed_backslash < data->args_nb &&
			i == data->tab_arg_nb[*printed_backslash])
	{
		*printed_backslash += 1;
		ft_putchar('\0');
	}
	if (data->output[i] && data->output[i] == '\n' && data->last_color != NULL)
	{
		ft_putstr("\033[0m\n");
		ft_putstr(data->last_color);
		i++;
	}
	else if (data->output[i])
		ft_putchar(data->output[i++]);
	return (i);
}

int		print_printf(t_data *data, int i)
{
	int	printed_backslash;
	int	backslash_last_pos;

	printed_backslash = 0;
	backslash_last_pos = 0;
	data->code = NULL;
	data->last_color = NULL;
	while (data->output[i])
		i = iterating_through_output(data, &printed_backslash, i);
	if (printed_backslash < data->args_nb &&
		data->tab_arg_nb[printed_backslash] == (int)ft_strlen(data->output) &&
		data->backslash > 0)
	{
		ft_putchar('\0');
		backslash_last_pos++;
	}
	if (data->last_color != NULL)
	{
		ft_putstr("\033[0m");
		free(data->last_color);
	}
	return (i + printed_backslash + backslash_last_pos);
}
