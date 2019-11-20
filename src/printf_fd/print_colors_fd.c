/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_colors.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/04 07:54:54 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 12:49:31 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int			handle_colors_fd(t_data *d, int i, int tmp, int fd)
{
	t_color	col;

	init_color_printf(&col);
	while (d->output[i] && d->output[i] != '}')
	{
		col.check = check_color_code(d, &col, i, 0);
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
	i = add_color_to_output(d, col, i);
	return (i);
}
