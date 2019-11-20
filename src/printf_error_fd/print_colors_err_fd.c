/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_colors.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/04 07:54:54 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 14:16:16 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int			handle_colors_err_fd(t_dataerr *d, int i, int tmp, int fd)
{
	t_colorerr	col;

	init_color_printf_err(&col);
	while (d->output[i] && d->output[i] != '}')
	{
		col.check = check_color_code_err(d, &col, i, 0);
		if (ft_strncmp(d->output + i, "eoc}", 4) == 0)
		{
			ft_putstr_fd("\033[0m", fd);
			d->code = NULL;
			return (i + 3);
		}
		else if (col.check == 0)
			return (tmp - 1);
		if (col.check > 0)
			i += 2;
		while (((d->output[i] < 'A' || d->output[i] > 'Z') &&
					d->output[i] != '}' && (col.back != -1 || col.text != -1)))
			i++;
	}
	if (!d->output[i] || col.check == 0)
		return (tmp - 1);
	i = add_color_to_output_err(d, col, i);
	return (i);
}
