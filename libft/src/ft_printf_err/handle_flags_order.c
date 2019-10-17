/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   Handle_flags_order.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 10:30:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 11:15:09 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf_err.h"

char			*handle_plus_minus_with_zero_err(t_dataerr data, char *arg)
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
