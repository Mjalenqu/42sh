/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_conversion.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 13:14:09 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 11:24:41 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	INIT OF ARRAY OF POINTER ON FT AND SELECTING ACCORDING FT
*/

char		*conversion_type(t_data *data, va_list va)
{
	char	*(*conv_pt[14])(va_list, t_data *);

	if (data->conv_type == 14)
		return (pourcent_conv(data));
	else if (data->conv_type == 15)
		return (NULL);
	else
	{
		conv_pt[0] = &(c_conv);
		conv_pt[1] = &(s_conv);
		conv_pt[2] = &(p_conv);
		conv_pt[4] = &(d_conv);
		conv_pt[5] = &(d_conv);
		conv_pt[6] = &(o_conv);
		conv_pt[7] = &(u_conv);
		conv_pt[8] = &(x_conv);
		conv_pt[9] = &(upper_x_conv);
		conv_pt[10] = &(b_conv);
		conv_pt[11] = &(upper_t_conv);
		conv_pt[12] = &(t_conv);
		conv_pt[13] = &(upper_w_conv);
		return ((*conv_pt[data->conv_type])(va, data));
	}
	return (NULL);
}

int			add_conv_2(t_data *data, char **arg, char *output)
{
	int		tmp_args_nb;

	tmp_args_nb = 0;
	if (*arg[0] == '-')
		data->minus++;
	if (ft_strlen(*arg) == 0 && (data->conv_type == 0 || data->conv_type == 1))
	{
		data->tab_arg_nb[data->backslash] = ft_strlen(output);
		if (data->width > 0)
			data->width--;
		tmp_args_nb++;
	}
	return (tmp_args_nb);
}

char		*add_conversion_output(t_data *data, char *output, va_list va,
		int tmp_args_nb)
{
	char	*arg;
	char	*tmp;

	arg = NULL;
	if (data->conv_type == 3)
		arg = f_conv(va, data);
	else
		arg = conversion_type(data, va);
	if (arg != NULL)
	{
		tmp_args_nb = add_conv_2(data, &arg, output);
		arg = add_flag_to_conv(*data, arg, -1);
		tmp = output;
		output = ft_strjoin(output, arg);
		if (tmp_args_nb > 0 && (data->conv_type != 1 &&
					ft_strcmp(arg, "(null)") != 0))
		{
			data->tab_arg_nb[data->backslash] += (ft_strlen(output) -
					data->tab_arg_nb[data->backslash]);
			data->backslash++;
		}
		free(tmp);
		free(arg);
	}
	return (output);
}
