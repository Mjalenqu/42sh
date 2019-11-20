/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/12 13:09:07 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 13:47:05 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

int		main_alias(t_process *p, t_var **var)
{
	char	*name;
	char	*data;
	int		k;
	int		error;

	error = 0;
	k = 0;
	if (!p->cmd[1])
		return (print_alias(*var));
	while (p->cmd[++k])
	{
		name = init_name(p->cmd[k]);
		data = init_data(p->cmd[k]);
		if (check_name(name) == 1)
			return (print_err(name, data));
		if (looking_for_aliases(p, k, name, data) == 1)
			error = 1;
	}
	return (error);
}

int		check_a(t_process *p, t_var **var)
{
	t_var	*start;
	t_var	*tmp;

	start = (*var);
	if (!p->cmd[1] || (ft_strcmp(p->cmd[1], "-a") != 0))
		return (0);
	while (start && start->type == ALIAS)
	{
		*var = start->next;
		free_one(start);
		start = *var;
	}
	while (*var)
	{
		if ((*var)->next && (*var)->next->type == ALIAS)
		{
			tmp = (*var)->next->next;
			free_one((*var)->next);
			(*var)->next = tmp;
		}
		else
			*var = (*var)->next;
	}
	stock(start, 5);
	return (1);
}

int		unalias_first(t_var **var, t_process *p, int k, t_var *start)
{
	if (*var && ft_strcmp(p->cmd[k], (*var)->name) == 0)
	{
		if (!(*var)->next)
		{
			free_one((*var));
			(*var) = NULL;
			return (1);
		}
		(*var) = (*var)->next;
		free_one(start);
		return (1);
	}
	return (0);
}

void	unalias_while(t_var **last, t_var **var)
{
	(*last) = (*var);
	(*var) = (*var)->next;
}

int		main_unalias(t_process *p, t_var **var)
{
	t_var	*start;
	t_var	*tmp;
	t_var	*last;
	int		k;

	k = 1;
	start = (*var);
	last = NULL;
	if (check_a(p, var) == 1)
		return (1);
	while (p->cmd[k])
	{
		if (unalias_first(var, p, k, start) == 1)
			return (1);
		while (*var && ft_strcmp(p->cmd[k], (*var)->name) != 0)
			unalias_while(&last, var);
		if (!(*var))
			return (error_unlias(p->cmd[k]));
		last->next = (*var)->next;
		tmp = (*var);
		(*var) = start;
		free_one(tmp);
		k++;
	}
	return (1);
}
