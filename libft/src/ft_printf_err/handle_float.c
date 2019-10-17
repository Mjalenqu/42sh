/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_float.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 11:13:53 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 11:16:22 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf_err.h"

int			determ_prec_err(t_dataerr data)
{
	if (data.tmp_prec[0] == '\0' && data.prec_dot == 0)
		return (6);
	else if ((data.tmp_prec[0] == '\0' && data.prec_dot == 1) || data.prec == 0)
		return (-1);
	else
		return (data.prec);
}

void		fill_num_err(t_floaterr *flt, t_dataerr *data)
{
	char		*tmp;
	char		*tmp2;

	if (flt->nb_float == 1.0 / 0.0 && data->f_inf++ == 0)
		flt->num = ft_strcpy(flt->num, "inf");
	else if (flt->nb_float != flt->nb_float && data->f_nan++ == 0)
		flt->num = ft_strcpy(flt->num, "nan");
	else
	{
		flt->nb_int = (long long)flt->nb_float;
		flt->nb_float = flt->nb_float - flt->nb_int;
		flt->nb_float = flt->nb_float * 10;
		if ((size_t)ft_strlen(flt->num) == flt->left_length)
			flt->num = free_strjoin(flt->num, ".");
		tmp2 = ft_itoa(flt->nb_int);
		flt->num = free_strjoin(flt->num, tmp2);
		if (flt->num[0] == '-')
		{
			tmp = flt->num;
			flt->num = ft_copy_part_str(flt->num, 1, 1);
			free(tmp);
		}
		free(tmp2);
	}
}

int			change_round_num_err(t_floaterr *flt, int i)
{
	flt->num[i] = '0';
	if (flt->num[i - 1] != '.')
		flt->num[--i] += 1;
	else
	{
		i -= 2;
		flt->num[i] += 1;
	}
	return (i);
}

char		*round_num_err(t_floaterr flt)
{
	int			i;

	i = ft_strlen(flt.num) - 1;
	if (flt.num[i] >= '5')
		i = change_round_num_err(&flt, i);
	while ((flt.num[i] > '9' && flt.num[i] < '0') || flt.num[i] == ':')
		i = change_round_num_err(&flt, i);
	flt.num[ft_strlen(flt.num) - 1] = '\0';
	if (flt.num[ft_strlen(flt.num) - 1] == '.')
		flt.num[ft_strlen(flt.num) - 1] = '\0';
	return (flt.num);
}

char		*handle_float_err(long double nb, t_dataerr *data)
{
	t_floaterr	flt;

	flt.num = ft_strnew(3);
	flt.left_length = check_num_length((long long)nb);
	flt.prec = determ_prec_err(*data);
	flt.nb_int = 0;
	if (nb < 0)
		flt.nb_float = -nb;
	else
		flt.nb_float = nb;
	while ((size_t)ft_strlen(flt.num) <= (flt.prec + flt.left_length + 1) &&
			ft_strcmp(flt.num, "inf") != 0 && ft_strcmp(flt.num, "nan") != 0)
		fill_num_err(&flt, data);
	if (ft_strcmp(flt.num, "inf") != 0 && ft_strcmp(flt.num, "nan") != 0)
		flt.num = round_num_err(flt);
	if (flt.num[0] == '.')
		ft_swap_let_string(flt.num, 0, 1);
	if (nb < 0)
		flt.num = add_char_begin_string_err(flt.num, "-");
	return (flt.num);
}
