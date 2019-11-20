/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias_norme.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 10:32:11 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 13:47:12 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	free_one(t_var *var)
{
	ft_strdel(&var->data);
	ft_strdel(&var->name);
	free(var);
}

int		looking_for_aliases(t_process *p, int k, char *name, char *data)
{
	t_var	*var;
	int		i;
	int		error;

	error = 0;
	i = 0;
	var = stock(NULL, 6);
	while (p->cmd[k][i] && p->cmd[k][i] != '=')
		i++;
	if (i == 0 || !p->cmd[k][i])
	{
		if (find_alias(p, k) == 1)
			error = 1;
	}
	else
		add_list_alias(&var, name, data);
	ft_free_deux(name, data);
	return (error);
}
