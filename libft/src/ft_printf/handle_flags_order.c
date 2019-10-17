/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Handle_flags_order.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 10:30:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/25 16:20:12 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char			*handle_plus_minus_with_zero(t_data data, char *arg)
{
	char		*tmp_arg;

	if (data.plus > 0 || arg[0] == '-')
	{
		tmp_arg = arg;
		arg = ft_copy_part_str(arg, 1, 1);
		free(tmp_arg);
	}
	return (arg);
}
