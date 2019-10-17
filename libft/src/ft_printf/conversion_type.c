/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conversion_type.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 13:52:33 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 14:07:47 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	GETTING CHAR CONV
*/

char					*c_conv(va_list va, t_data *data)
{
	char				*letter;

	data->code = NULL;
	letter = ft_strnew(1);
	letter[0] = va_arg(va, int);
	letter[1] = '\0';
	return (letter);
}

char					*s_conv(va_list va, t_data *data)
{
	char				*string;
	char				*join;
	char				*tmp;
	char				*tmp2;

	join = ft_strnew(0);
	tmp = join;
	string = va_arg(va, char*);
	if (string != NULL)
	{
		join = ft_strjoin(join, string);
		if (ft_strcmp(string, "") == 0 && data->width > 0)
		{
			tmp2 = join;
			join = ft_strjoin(" ", join);
			free(tmp2);
		}
	}
	else
		join = ft_strjoin(join, "(null)");
	free(tmp);
	return (join);
}

char					*p_conv(va_list va, t_data *data)
{
	char				*address;
	char				*tmp;

	address = va_arg(va, char*);
	address = ft_itoa_base_uns(((long long)address), 16);
	tmp = address;
	if (ft_strcmp(address, "0") == 0 && data->prec_dot == 1 && data->prec == 0)
		address[0] = '\0';
	address = ft_strjoin("0x", address);
	free(tmp);
	return (address);
}

char					*d_conv(va_list va, t_data *data)
{
	long long			nb;
	char				*num;

	nb = 0;
	if (data->length[0] == '\0')
		nb = va_arg(va, int);
	else if (ft_strcmp(data->length, "h") == 0)
		nb = (short)va_arg(va, int);
	else if (ft_strcmp(data->length, "hh") == 0)
		nb = (char)va_arg(va, int);
	else if (ft_strcmp(data->length, "l") == 0)
		nb = va_arg(va, long);
	else if (ft_strcmp(data->length, "ll") == 0)
		nb = va_arg(va, long long);
	num = ft_itoa((unsigned long long)nb);
	if (nb == 0 && data->prec_dot == 1 && data->prec == 0)
	{
		num[0] = '\0';
		data->backslash++;
	}
	return (num);
}

char					*u_conv(va_list va, t_data *data)
{
	unsigned long long	nb;
	char				*num;

	nb = 0;
	if (data->length[0] == '\0')
		nb = va_arg(va, unsigned int);
	else if (ft_strcmp(data->length, "hh") == 0)
		nb = (unsigned char)va_arg(va, unsigned int);
	else if (ft_strcmp(data->length, "h") == 0)
		nb = (unsigned short)va_arg(va, unsigned int);
	else if (ft_strcmp(data->length, "l") == 0)
		nb = (unsigned long long)va_arg(va, unsigned long);
	else if (ft_strcmp(data->length, "ll") == 0)
		nb = va_arg(va, unsigned long long);
	num = ft_itoa_base_uns((unsigned long long)nb, 10);
	if (ft_strcmp(num, "0") == 0 && data->prec_dot == 1 && data->prec == 0)
		num[0] = '\0';
	return (num);
}
