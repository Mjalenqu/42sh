/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_prec_and_width.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 11:35:24 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 15:16:03 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char			*add_prec_to_pointer(t_data data, char *arg)
{
	char		*new_arg;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (ft_strlen(arg) > data.prec)
		return (arg);
	new_arg = ft_strnew(data.prec + 2);
	while (i <= 1)
	{
		new_arg[i++] = arg[j++];
	}
	while ((i - 3 + ft_strlen(arg)) <= data.prec)
		new_arg[i++] = '0';
	while (arg[j])
		new_arg[i++] = arg[j++];
	free(arg);
	new_arg[i] = '\0';
	return (new_arg);
}

char			*add_prec_to_string(t_data data, char *arg)
{
	int			i;
	char		*new_arg;

	i = -1;
	if (ft_strlen(arg) > data.prec)
	{
		new_arg = ft_strnew(data.prec);
		while (++i < data.prec)
			new_arg[i] = arg[i];
		new_arg[i] = '\0';
		free(arg);
		return (new_arg);
	}
	return (arg);
}

char			*handle_width(t_data data, char *arg)
{
	int			i;

	i = 0;
	while (data.flag[i])
	{
		if (data.flag[i++] == '-')
			return (arg);
	}
	if (arg != NULL)
	{
		if (data.prec_dot == 1 && data.prec == 0 &&
				(is_contained_in("0", data.flag, 0) == 1))
			while (ft_strlen(arg) < data.width)
				arg = add_char_begin_string(arg, "0");
		else
		{
			while (ft_strlen(arg) < data.width)
				arg = add_char_begin_string(arg, " ");
		}
	}
	return (arg);
}

char			*handle_prec(t_data data, char *arg)
{
	if (data.prec_dot == 1 && (data.conv_type >= 4 && data.conv_type <= 9))
	{
		arg = handle_plus_minus_with_zero(data, arg);
		while (ft_strlen(arg) < data.prec)
			arg = add_char_begin_string(arg, "0");
		if (data.minus > 0 && arg[0] != '-')
			arg = add_char_begin_string(arg, "-");
	}
	if (data.prec_dot == 1 && data.conv_type == 2)
		arg = add_prec_to_pointer(data, arg);
	if (data.prec_dot == 1 && data.conv_type == 1)
		arg = add_prec_to_string(data, arg);
	return (arg);
}
