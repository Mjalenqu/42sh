/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_export.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/20 15:23:43 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 10:19:01 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/exec.h"

static void			export_var(t_process *p, t_var **var)
{
	t_var			*tmp;
	int				i;

	i = 1;
	while (p->cmd[i])
	{
		tmp = *var;
		if (find_equal(p->cmd[i]) == 1)
			ft_setenv(p, var);
		else
		{
			while (tmp)
			{
				if (ft_strcmp(p->cmd[i], tmp->name) == 0)
					tmp->type = ENVIRONEMENT;
				tmp = tmp->next;
			}
		}
		i++;
	}
}

static int			print_error(int status)
{
	if (status == 1)
	{
		ft_printf_err("42sh: export: {B.T.red.}error{eoc}:");
		ft_printf_err(" Argument required\n");
	}
	return (0);
}

int					ft_export(t_process *p, t_var **var)
{
	if (!(p->cmd[1]))
		return (print_error(1));
	else if (ft_strcmp(p->cmd[1], "-p") == 0)
		print_env(*var);
	else
		export_var(p, var);
	return (0);
}
