/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jump.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/25 08:12:14 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 07:35:14 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		jump_left(t_pos *pos)
{
	if (pos->is_complete == 0 && pos->act_co == 2 && pos->ans[pos->let_nb])
		return ;
	if (pos->let_nb == 0)
		return ;
	if (ft_isspace(pos->ans[pos->let_nb]) == 0 && ft_isspace(pos->ans[pos->let_nb - 1]) == 1)
	{
		pos->let_nb--;
		pos->act_co--;
	}
	if (ft_isspace(pos->ans[pos->let_nb]) == 1)
		while (pos->let_nb > 0 && ft_isspace(pos->ans[pos->let_nb]) == 1)
		{
			pos->debug2 = pos->ans[pos->let_nb];
			pos->let_nb--;
			/*if (pos->act_co > 0)
				pos->act_co--;
			else if (pos->act_co <= 0 && pos->act_li > pos->start_li)
			{
				pos->act_co = pos->max_co - 1;
				pos->act_li--;
			}*/
			if (pos->act_co > 0)
				pos->act_co--;
			else
			{
				if (pos->act_co == 0 && pos->act_li > pos->start_li)
				{
					pos->act_li--;
					if (pos->ans[pos->let_nb - 1] == '\n')
						pos->act_co = len_of_previous_line(pos);
					else
						pos->act_co = pos->max_co - 1;
				}
			}
		}
	while (pos->let_nb > 0 && ft_isspace(pos->ans[pos->let_nb]) == 0)
	{
		if (ft_isspace(pos->ans[pos->let_nb - 1]) == 1)
			break ;
		pos->let_nb--;
		if (pos->act_co > 0)
			pos->act_co--;
		else if (pos->act_co <= 0 && pos->act_li > pos->start_li)
		{
			pos->act_co = pos->max_co - 1;
			pos->act_li--;
		}
	}
	pos->debug = pos->act_co;
	pos->debug2 = pos->act_li;
	pos->debug3 = pos->let_nb;
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

void		jump_right(t_pos *pos)
{
	if (pos->let_nb >= pos->len_ans)
		return ;
	if (pos->ans[pos->let_nb] && ft_isspace(pos->ans[pos->let_nb]) == 0)
	{
		while (pos->ans[pos->let_nb] && ft_isspace(pos->ans[pos->let_nb]) == 0)
		{
			pos->let_nb++;
			if ((pos->act_co == pos->max_co && pos->ans[pos->let_nb]) || pos->ans[pos->let_nb] == '\n')
			{
				pos->act_co = 1;
				pos->act_li++;
			}
			else
				pos->act_co++;
		}
	}
	while (pos->ans[pos->let_nb] && ft_isspace(pos->ans[pos->let_nb]) == 1)
	{
		pos->let_nb++;
		if (pos->act_co == pos->max_co && pos->ans[pos->let_nb])
		{
			pos->act_co = 1;
			pos->act_li++;
		}
		else
			pos->act_co++;
	}
}

void		go_hard(t_pos *pos)
{
	while (pos->ans[pos->let_nb] && pos->ans[pos->let_nb] != '\n')
	{
		pos->let_nb++;
		if (pos->act_co == pos->max_co - 1)
		{
			pos->act_co = 0;
			pos->act_li++;
		}
		else
			pos->act_co++;
	}
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

void		or_go_home(t_pos *pos)
{
	while (pos->let_nb > 0 && (pos->ans[pos->let_nb - 1] != '\n'))
	{
		pos->let_nb--;
		if (pos->act_co == 0)
		{ 
			pos->act_co = pos->max_co - 1;
			pos->act_li--;
		}
		else
			pos->act_co--;
	}
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}

void		jump_UP(t_pos *pos)
{
	if (pos->is_complete == 0)
		return ;
}

void		jump_DOWN(t_pos *pos)
{
	if (pos->is_complete == 0)
		return ;
	
}

void		find_jump(char *buf, t_pos *pos)
{
	if (ft_strcmp(buf + 2, "[A") == 0)
		jump_UP(pos);
	if (ft_strcmp(buf + 2, "[B") == 0)
		jump_DOWN(pos);
	if (ft_strcmp(buf + 2, "[D") == 0)
		jump_left(pos);
	else if (ft_strcmp(buf + 2, "[C") == 0)
		jump_right(pos);
	else if (ft_strcmp(buf + 1, "[F") == 0)
		go_hard(pos);
	else if (ft_strcmp(buf + 1, "[H") == 0)
		or_go_home(pos);
}
