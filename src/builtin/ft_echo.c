/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_echo.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/26 15:00:57 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/exec.h"

int			ft_echo_simple(t_process *p, t_var **var, t_pos *pos)
{
	int		i;

	i = 1;
	var = NULL;
	while (p->cmd[i] != NULL)
	{
		if (i != 1)
			ft_printf_fd(" ");
		ft_printf_fd("%s", p->cmd[i]);
		i++;
	}
	if (write(pos->act_fd_out, "\n", 1) == -1)
	{
		ft_printf_err_fd("42sh: echo: write error: Bad file descriptor\n");
		return (1);
	}
	return (0);
}

int			ft_echo_no_line(t_process *p, t_var **var, t_pos *pos)
{
	int		i;

	i = 2;
	var = NULL;
	while (p->cmd[i] != NULL)
	{
		if (i != 2)
			ft_printf_fd(" ");
		if (write(pos->act_fd_out, p->cmd[i], ft_strlen(p->cmd[i])) == -1)
		{
			ft_printf_err_fd("42sh: echo: write error: Bad file descriptor\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int			ft_echo(t_process *p, t_var **var)
{
	t_pos	*pos;

	pos = to_stock(NULL, 1);
	if (p->cmd[1])
	{
		if (ft_strcmp(p->cmd[1], "-n") == 0)
			return (ft_echo_no_line(p, var, pos));
	}
	return (ft_echo_simple(p, var, pos));
}
