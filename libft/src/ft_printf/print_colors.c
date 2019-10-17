/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_colors.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/04 07:54:54 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 09:45:26 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		add_color_code(t_data *data, t_color *col)
{
	char	*num;

	num = NULL;
	if (col->bold == 1)
		data->code = free_strjoin(data->code, "1;");
	if (col->underlined == 1)
		data->code = free_strjoin(data->code, "4;");
	if (col->italic == 1)
		data->code = free_strjoin(data->code, "3;");
	if (col->blinking == 1)
		data->code = free_strjoin(data->code, "5;");
	if (col->text > 0)
	{
		num = ft_itoa(col->text);
		data->code = free_strjoin(data->code, num);
		data->code = free_strjoin(data->code, ";");
		free(num);
	}
	if (col->back > 0)
	{
		num = ft_itoa(col->back);
		data->code = free_strjoin(data->code, num);
		data->code = free_strjoin(data->code, ";");
		free(num);
	}
}

int			add_color_to_output(t_data *data, t_color col, int i)
{
	int		j;

	data->code = ft_strdup("\033[");
	add_color_code(data, &col);
	j = ft_strlen(data->code);
	data->code[j - 1] = 'm';
	ft_putstr(data->code);
	if (data->last_color != NULL)
		free(data->last_color);
	data->last_color = ft_strnew(ft_strlen(data->code));
	data->last_color = ft_strcpy(data->last_color, data->code);
	free(data->code);
	return (i);
}

int			search_color(int i, char *output, int usage)
{
	int		tmp;

	tmp = -1;
	if (ft_strncmp(output + i, "grey.", 5) == 0)
		tmp = usage == 0 ? 40 : 30;
	if (ft_strncmp(output + i, "red.", 4) == 0)
		tmp = usage == 0 ? 41 : 31;
	if (ft_strncmp(output + i, "green.", 6) == 0)
		tmp = usage == 0 ? 42 : 32;
	if (ft_strncmp(output + i, "yellow.", 7) == 0)
		tmp = usage == 0 ? 43 : 33;
	if (ft_strncmp(output + i, "blue.", 5) == 0)
		tmp = usage == 0 ? 44 : 34;
	if (ft_strncmp(output + i, "purple.", 7) == 0)
		tmp = usage == 0 ? 45 : 35;
	if (ft_strncmp(output + i, "cyan.", 5) == 0)
		tmp = usage == 0 ? 46 : 36;
	if (ft_strncmp(output + i, "white.", 6) == 0)
		tmp = usage == 0 ? 47 : 37;
	return (tmp);
}

int			check_color_code(t_data *d, t_color *col, int i, int check)
{
	if (d->output[i] == 'B' && d->output[i + 1] == '.' && check++ >= 0)
		col->bold = 1;
	else if (d->output[i] == 'U' && d->output[i + 1] == '.' && check++ >= 0)
		col->underlined = 1;
	else if (d->output[i] == 'I' && d->output[i + 1] == '.' && check++ >= 0)
		col->italic = 1;
	else if (d->output[i] == 'F' && d->output[i + 1] == '.' && check++ >= 0)
		col->blinking = 1;
	else if (d->output[i] == 'T' && d->output[i + 1] == '.' && check++ >= 0)
		col->text = search_color(i + 2, d->output, 1);
	else if (d->output[i] == 'S' && d->output[i + 1] == '.' && check++ >= 0)
		col->back = search_color(i + 2, d->output, 0);
	return (check);
}

int			handle_colors(t_data *d, int i, int tmp)
{
	t_color	col;

	init_color_printf(&col);
	while (d->output[i] && d->output[i] != '}')
	{
		col.check = check_color_code(d, &col, i, 0);
		if (ft_strncmp(d->output + i, "eoc}", 4) == 0)
		{
			ft_putstr("\033[0m");
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
