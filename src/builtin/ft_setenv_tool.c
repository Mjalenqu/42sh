/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_setenv_tool.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:23:43 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

char		**init_al_tab_content(t_process *p, int i)
{
	char	**al;

	al = ft_malloc(sizeof(char *) * 3);
	al[0] = init_name(p->cmd[i]);
	al[1] = init_data(p->cmd[i]);
	if (!al[1])
		al[1] = ft_strnew(0);
	al[2] = 0;
	return (al);
}

void		print_env(t_var *var)
{
	while (var)
	{
		if (var->type == ENVIRONEMENT)
		{
			ft_printf_fd("%s=", var->name);
			ft_printf_fd("%s\n", var->data);
		}
		var = var->next;
	}
}

int			print_err_setenv(char **al)
{
	ft_free_tab(al);
	ft_printf_err_fd("42sh: setenv: ambiguous value name\n");
	return (-1);
}
