/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 14:56:11 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 11:38:49 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FREE DATA ELEMS MALLOCED IN DETERM DATA
*/

t_data		*init_data_printf(t_data *data)
{
	data->conv = 0;
	data->conv_type = 0;
	data->flag = ft_strnew(0);
	data->tmp_width = ft_strnew(0);
	data->width = 0;
	data->prec_dot = 0;
	data->flag_minus = 0;
	data->minus = 0;
	data->tmp_prec = ft_strnew(0);
	data->length = ft_strnew(0);
	data->f_inf = 0;
	data->f_nan = 0;
	data->diez_length = 0;
	return (data);
}

long		*init_tab_arg_nb(t_data data)
{
	int		i;

	i = 0;
	if (!(data.tab_arg_nb = (long*)ft_malloc(sizeof(long) * data.args_nb)))
		return (NULL);
	while (i < data.args_nb)
	{
		data.tab_arg_nb[i] = -1;
		i++;
	}
	return (data.tab_arg_nb);
}

char		*free_strjoin(char *str1, char *str2)
{
	char	*tmp;

	tmp = str1;
	str1 = ft_strjoin(str1, str2);
	free(tmp);
	return (str1);
}

int			check_non_valid_conv(t_data *data)
{
	if (data->conv == 0 && data->conv_type == 15)
	{
		while (--data->width > 0)
			data->output = add_char_end_string(data->output, " ", 0);
		return (1);
	}
	else
		return (0);
}

void		free_data(t_data *data, int usage)
{
	if (usage == 0)
	{
		free(data->flag);
		free(data->tmp_width);
		free(data->tmp_prec);
		free(data->length);
	}
	else if (usage == 1)
	{
		free(data->tab_arg_nb);
		free(data->output);
	}
}
