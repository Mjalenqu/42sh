/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   jump_up_dowm.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/17 07:43:32 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/21 10:32:20 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		jump_up(t_pos *pos)
{
	t_pos	clone;

	clone.act_co = pos->act_co;
	clone.act_li = pos->act_li;
	while (pos->let_nb > 0)
	{
		left_arrow(pos);
		if (pos->is_complete == 0 && pos->let_nb > 0 &&
		pos->ans[pos->let_nb - 1] == '\n' && pos->act_co == pos->len_prompt)
			break ;
		if (pos->act_co <= clone.act_co && pos->act_li < clone.act_li)
			break ;
	}
}

void		jump_down(t_pos *pos)
{
	t_pos	clone;
	int		loop;

	loop = 0;
	clone.act_co = pos->act_co;
	clone.act_li = pos->act_li;
	while (pos->ans[pos->let_nb])
	{
		if (pos->ans[pos->let_nb] == '\n')
			loop += 1 + pos->act_li - clone.act_li;
		if (loop >= 2)
			break ;
		right_arrow(pos);
		if (pos->act_co >= clone.act_co && pos->act_li > clone.act_li)
			break ;
	}
}
