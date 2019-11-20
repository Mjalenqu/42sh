/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unset.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/20 15:49:17 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 14:47:31 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/exec.h"

int			ft_unset_var(char *name, t_var **ptr_var)
{
	if (remove_list_var(ptr_var, ENVIRONEMENT, name))
		return (1);
	else if (remove_list_var(ptr_var, LOCAL, name))
		return (1);
	else if (ft_get_val(name, *ptr_var, SPE) != NULL)
	{
		ft_printf_err_fd("can not unset special variable: {B.T.red.}%s{eoc}\n",
				name);
		return (1);
	}
	return (0);
}

int			ft_unset(t_process *p, t_var **ptr_var)
{
	int i;

	i = 0;
	while (p->cmd[++i])
	{
		if (!(ft_unset_var(p->cmd[i], ptr_var)))
			ft_printf_err_fd("{B.T.red.}%s{eoc} not found\n", p->cmd[i]);
	}
	stock(*ptr_var, 5);
	return (0);
}
