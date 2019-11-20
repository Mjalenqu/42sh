/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_shtheme.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 11:00:50 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static void		change_theme(t_pos *pos, char **cmd)
{
	if (cmd[1][0] == '1')
		pos->shtheme = 1;
	else if (cmd[1][0] == '2')
		pos->shtheme = 2;
	else if (cmd[1][0] == '3')
		pos->shtheme = 3;
	else if (cmd[1][0] == '4')
		pos->shtheme = 4;
	else if (cmd[1][0] == '5')
		pos->shtheme = 5;
	else if (ft_strcmp(cmd[1], "return") == 0)
		pos->ret = pos->ret == 0 ? 1 : 0;
}

int				ft_shtheme(t_process *p, t_var **var)
{
	t_pos	*pos;

	(void)var;
	pos = to_stock(NULL, 1);
	if (p && p->cmd && p->cmd[1] && (ft_strlen(p->cmd[1]) == 1 ||
			ft_strcmp(p->cmd[1], "return") == 0) && !(p->cmd[2]))
		change_theme(pos, p->cmd);
	else if (p && p->cmd && p->cmd[1] == NULL)
		pos->shtheme = pos->shtheme == 5 ? 1 : pos->shtheme + 1;
	else
	{
		ft_printf_err_fd("42sh: shtheme: usage: shtheme [1|2|3|4|5]\n");
		return (1);
	}
	return (0);
}
