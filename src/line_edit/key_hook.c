/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_hook.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/04 18:24:48 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 09:57:09 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"

void	display(char *str, t_all *all, int *start)
{
	int i;

	i = all->wind.pos_col;
	if ((ft_strlen(str) / all->wind.max_col) > all->wind.max_line - all->wind.srt_line)
	{
		tputs(tgoto(tgetstr("cm", NULL), all->wind.max_col + 1, all->wind.max_line + 1), 1, ft_put_c);
		(*start)--;
		printf("passe\n");
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, (*start)), 1, ft_put_c);
	tputs(tgetstr("cd", NULL), 1, ft_put_c);
	ft_putcolor(BRED, "prompt->", RESET);
	if (!str || (str && str[0] == '\0'))
		return ;
	if (i == ft_strlen(str))
	{
			tputs(tgetstr("ve", NULL), 1, ft_put_c);
			write(1, str, ft_strlen(str));
	}
	else
	{
		tputs(tgetstr("vi", NULL), 1, ft_put_c);
		write(1, str, i);
		tputs(tgoto(tgetstr("cm", NULL),
						i + 8, all->wind.pos_line), 1, ft_put_c);
		tputs(tgetstr("mr", NULL), 1, ft_put_c);
		ft_putchar(str[i]);
		tputs(tgetstr("me", NULL), 1, ft_put_c);
		write(1, str + i + 1, ft_strlen(str) - i);
	}
}

int		ft_put_c(int c)
{
	write(1, &c, 1);
	return (0);
}

char	*remove_char(char **str, int i)
{
	char	*res;
	char	*tmp;

	if (i < 1 || !(*str))
		return (*str);
	if (i == 1)
		res = ft_strsub(*str, 1, ft_strlen(*str) - 1);
	else
	{
		res = ft_strsub(*str, 0, i - 1);
		tmp = ft_strsub(*str, i, ft_strlen(*str));
		ft_strjoin_free(&res, tmp);
	}
	ft_strdel(str);
	return (res);
}

int		check_key(long c, t_all *all, char **res)
{
	if (c == LEFT)
	{
		if (all->wind.pos_col > 1)
			(all->wind.pos_col) -= 1;
		else
			all->wind.pos_col = 0;
	}
	else if (c == RIGHT)
	{
		if ((*res) && all->wind.pos_col < ft_strlen(*res))
			all->wind.pos_col++;
	}
	else if (c == UP || c == DOWN || c == ALT_L || c == ALT_R)
		return (0);
	else if (c == HOME)
		all->wind.pos_col = 0;
	else if (c == END)
		all->wind.pos_col = ft_strlen(*res);
	else if (c == BACK)
		do_back(all, res);
	else
		return (1);
	return (0);
}

char	*check_char(char *res, long c, t_all *all)
{
	int		i;
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	i = check_key(c, all, &res);
	if (i == 0)
		return (res);
	if ((res && res[0] == '\0') || !res)
	{
		ft_strdel(&res);
		res = malloc(sizeof(char) * 2);
		res[0] = c;
		res[1] = '\0';
	}
	else
		ft_strjoin_insert(&res, tmp, all->wind.pos_col);
	all->wind.pos_col++;
	return (res);
}

void	key_is_up(t_all **all)
{
	if ((*all)->last->cmd && (*all)->history &&
							(*all)->history->next == NULL)
		(*all)->save = ft_strdup((*all)->last->cmd);
	if ((*all)->history->prev == NULL)
		return ;
	if ((*all)->history && (*all)->history->prev)
	{
		(*all)->history = (*all)->history->prev;
		(*all)->wind.pos_col = ft_strlen((*all)->history->cmd);
		(*all)->last->cmd = ft_strdup((*all)->history->cmd);
		tputs(tgoto(tgetstr("cm", NULL),
				(*all)->wind.pos_col, (*all)->wind.pos_line),
			1, ft_put_c);
	}
}

void	key_is_down(t_all **all)
{
	if ((*all)->history->next == NULL && (*all)->save)
		(*all)->last->cmd = ft_strdup((*all)->save);
	else if ((*all)->history && (*all)->history->next)
	{
		(*all)->history = (*all)->history->next;
		(*all)->last->cmd = ft_strdup((*all)->history->cmd);
	}
	(*all)->wind.pos_col = ft_strlen((*all)->last->cmd);
	tputs(tgoto(tgetstr("cm", NULL),
			(*all)->wind.pos_col, (*all)->wind.pos_line),
			1, ft_put_c);
}

int		*key_hook(t_all *all)
{
	long		key;
	int			i;

	key = 0;
	i = 0;
	all->wind = init_wind();
	ft_putcolor(BRED, all->prompt, RESET);
	all->wind.pos_col = 0;
	all->wind.srt_col = 0;
	all->wind.srt_line = all->wind.pos_line;
//	printf("line1 = %d\n", all->wind.srt_line);
	while (all->last->next != NULL)
		all->last = all->last->next;
	if (all->last && all->last->cmd && all->last->cmd[0] != '\0')
	{
		all->last->next = add_history(all);
		all->last = all->last->next;
		all->history = all->last;
	}
	while (read(0, &key, 8) > -1)
	{
		if (key == 10)
		{
			do_the_enter(&all);
			return (0);
		}
		if (key == UP)
			key_is_up(&all);
		if (key == DOWN)
			key_is_down(&all);
		if (key == ALT_L)
			jump_left(&all);
		if (key == ALT_R)
			jump_right(&all);
		all->last->cmd = check_char(all->last->cmd, key, all);
//		printf("line1 = %d -- ", all->wind.srt_line);
		display(all->last->cmd, all, &all->wind.srt_line);
//		printf("line2 = %d --\n", all->wind.srt_line);
		key = 0;
	}
	return (0);
}
