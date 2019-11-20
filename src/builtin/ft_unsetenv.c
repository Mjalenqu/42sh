/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unsetenv.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/13 15:50:21 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static int	unsetenv_rules(t_process *p)
{
	if (p->cmd[1] && ft_strcmp(p->cmd[1], "-u") == 0)
	{
		ft_printf_err_fd("42sh: unsetenv: usage: unsetenv [NAME]\n");
		return (0);
	}
	return (1);
}

int			ft_unsetenv(t_process *p, t_var **var)
{
	int		i;

	i = 1;
	if (*var && p->cmd[i])
	{
		while (p->cmd[i])
		{
			if (unsetenv_rules(p) == 0)
				return (0);
			if (remove_list_var(var, ENVIRONEMENT, p->cmd[i]) == 1)
				stock(*var, 5);
			else
				ft_printf_err_fd("42sh: unsetenv: var %s not found\n",
						p->cmd[i]);
			i++;
		}
		return (0);
	}
	else if (*var == NULL)
		ft_printf_err_fd("42sh: unsetenv: environment not set\n");
	else
		ft_printf_err_fd("42sh: unsetenv: bad parameters, use -u for usage\n");
	return (-1);
}
