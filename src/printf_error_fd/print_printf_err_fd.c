/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_printf.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 14:54:19 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 14:16:30 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int		iterating_through_output_err_fd(t_dataerr *data, int *printed_backslash,
		int i, int fd)
{
	if (data->output[i] && data->output[i] == '{' &&
		check_if_color_err(data, i + 1))
	{
		i = handle_colors_err_fd(data, i + 1, i + 1, fd);
		if (data->output[i] == '}')
			return (i + 1);
	}
	if (data->backslash > 0 && *printed_backslash <= data->backslash &&
			*printed_backslash < data->args_nb &&
			i == data->tab_arg_nb[*printed_backslash])
	{
		*printed_backslash += 1;
		ft_putchar_fd('\0', fd);
	}
	if (data->output[i] && data->output[i] == '\n' && data->last_color != NULL)
	{
		ft_putstr_fd("\033[0m\n", fd);
		ft_putstr_fd(data->last_color, fd);
		i++;
	}
	else if (data->output[i])
		ft_putchar_fd(data->output[i++], fd);
	return (i);
}

int		print_printf_err_fd(t_dataerr *data, int i, int fd)
{
	int	printed_backslash;
	int	backslash_last_pos;

	printed_backslash = 0;
	backslash_last_pos = 0;
	data->code = NULL;
	data->last_color = NULL;
	while (data->output[i])
		i = iterating_through_output_err_fd(data, &printed_backslash, i, fd);
	if (printed_backslash < data->args_nb &&
		data->tab_arg_nb[printed_backslash] == (int)ft_strlen(data->output) &&
		data->backslash > 0)
	{
		ft_putchar_fd('\0', fd);
		backslash_last_pos++;
	}
	if (data->last_color != NULL)
	{
		ft_putstr_fd("\033[0m", fd);
		free(data->last_color);
	}
	return (i + printed_backslash + backslash_last_pos);
}
