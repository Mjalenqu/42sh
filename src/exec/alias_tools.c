/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/25 15:57:47 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void		add_alias(t_var **var, char *name, char *data)
{
	t_var	*start;

	start = ft_malloc(sizeof(t_var));
	start->name = name;
	start->data = data;
	start->type = ALIAS;
	start->next = (*var);
	(*var) = start;
}

int			find_alias(t_process *p, int k)
{
	t_var	*tmp;

	tmp = stock(NULL, 6);
	while (tmp && ft_strcmp(p->cmd[k], tmp->name))
		tmp = tmp->next;
	if (!tmp)
	{
		ft_printf_err_fd("42sh: alias: %s: not found\n", p->cmd[k]);
		return (1);
	}
	ft_printf_fd("%s=%s\n", tmp->name, tmp->data);
	return (0);
}

void		add_to_alias(t_var **var, char *name, char *data, t_var *prev)
{
	(*var) = ft_malloc(sizeof(t_var));
	prev->next = (*var);
	(*var)->next = NULL;
	(*var)->name = ft_strdup(name);
	(*var)->data = ft_strdup(data);
	(*var)->type = ALIAS;
}

void		add_list_alias(t_var **var, char *name, char *data)
{
	t_var	*prev;

	prev = NULL;
	if (!(*var))
	{
		ft_printf_fd("list alias");
		add_alias(var, name, data);
		stock(*var, 5);
		return ;
	}
	while (*var)
	{
		if (ft_strcmp(name, (*var)->name) == 0)
			break ;
		prev = (*var);
		(*var) = (*var)->next;
	}
	if (!(*var))
	{
		add_to_alias(var, name, data, prev);
		return ;
	}
	ft_strdel(&(*var)->data);
	(*var)->data = ft_strdup(data);
}
