/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cut.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 09:34:46 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 20:19:33 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

char	*remove_cut(char *str, int start, int end)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str || str[0] == '\0' || (start == 0 && end == ft_strlen(str)))
	{
		ft_strdel(&str);
		res = ft_strdup("");
		return (res);
	}
	res = ft_malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		while (str[i] && i >= start && i <= end)
			i++;
		res[j] = str[i];
		if (str[i])
			i++;
		j++;
	}
	res[j] = '\0';
	ft_strdel(&str);
	return (res);
}

void	cut_char(t_pos *pos)
{
	int len;

	if (pos->start_select == -1)
	{
		pos->ans_printed = 1;
		return ;
	}
	save_char(pos);
	if (pos->start_select < pos->let_nb)
	{
		pos->ans = remove_cut(pos->ans, pos->start_select, pos->let_nb);
		len = pos->let_nb - pos->start_select;
		pos->let_nb = pos->start_select;
		pos->act_co -= len;
	}
	else
		pos->ans = remove_cut(pos->ans, pos->let_nb, pos->start_select);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	pos->start_select = -1;
	clear_and_print(pos);
}

void	paste(t_pos *pos)
{
	char	*tmp;
	char	co[2];
	int		i;

	tmp = stock(NULL, 4);
	if (tmp == NULL)
	{
		pos->ans_printed = 1;
		return ;
	}
	i = 0;
	co[1] = '\0';
	while (tmp[i])
	{
		co[0] = tmp[i];
		input_is_printable_char(pos, co);
		i++;
	}
	clear_and_print(pos);
	short_update(pos, go_to_let_nb(pos));
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li),
			1, ft_putchar);
	pos->ans_printed = 1;
}

void	copy(t_pos *pos)
{
	if (pos->start_select == -1)
	{
		pos->ans_printed = 1;
		return ;
	}
	save_char(pos);
	pos->start_select = -1;
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	clear_and_print(pos);
}

void	check_copy(unsigned char *buf, t_pos *pos)
{
	if (buf[0] == 226 && buf[1] == 137 && buf[2] == 136)
		cut_char(pos);
	else if (buf[0] == 195 && buf[1] == 167)
		copy(pos);
	else if (buf[0] == 226 && buf[1] == 136 && buf[2] == 154)
		paste(pos);
	if (pos->saved_ans)
		pos->saved_ans = ft_secure_free(pos->saved_ans);
	pos->saved_ans = ft_strdup(pos->ans);
	if (ft_strlen(pos->ans) > 0)
		pos->history_mode = 1;
	else
		pos->history_mode = 0;
	pos->start_select = -1;
}
