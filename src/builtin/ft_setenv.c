/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_setenv.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/13 14:08:25 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void		add_setenv(t_var **var, char *name, char *data, int usage)
{
	t_var	*start;

	if (usage == 0)
	{
		start = ft_malloc(sizeof(t_var));
		start->name = ft_strdup(name);
		start->data = ft_strdup(data);
		start->type = ENVIRONEMENT;
		start->next = (*var);
		(*var) = start;
	}
	else if (usage == 1)
	{
		(*var) = ft_malloc(sizeof(t_var));
		(*var)->next = NULL;
		(*var)->name = ft_strdup(name);
		(*var)->data = ft_strdup(data);
		(*var)->type = ENVIRONEMENT;
	}
}

static int	setenv_rules(t_process *p, char **al)
{
	if (p->cmd[1] && !p->cmd[2] && ft_strcmp(p->cmd[1], "-u") == 0)
	{
		ft_printf_err_fd("42sh: setenv: usage: setenv [NAME=data, NAME]\n");
		ft_free_tab(al);
		return (0);
	}
	return (1);
}

void		add_var_to_env(t_var *var, char *name, char *data, t_var *prev)
{
	if (!(var))
	{
		add_setenv(&var, name, data, 0);
		stock(var, 5);
		return ;
	}
	while (var)
	{
		if (ft_strcmp(name, (var)->name) == 0 && var->type == ENVIRONEMENT)
			break ;
		prev = (var);
		(var) = (var)->next;
	}
	if (!(var))
	{
		add_setenv(&var, name, data, 1);
		prev->next = (var);
		return ;
	}
	if (data && ft_strlen(data) > 0)
	{
		ft_strdel(&(var)->data);
		(var)->data = ft_strdup(data);
	}
}

int			setenv_through_cmd_passed(t_process *p, t_var **var, char **al,
		int i)
{
	int		check;

	check = 0;
	while (p->cmd[++i])
	{
		al = init_al_tab_content(p, i);
		remoove_quote(&al);
		if (setenv_rules(p, al) == 0)
			return (0);
		if (check_name(al[0]) == 1 || p->cmd[i][0] == '=')
			return (print_err_setenv(al));
		add_var_to_env(*var, al[0], al[1], NULL);
		check = 0;
		ft_free_tab(al);
	}
	return (check);
}

int			ft_setenv(t_process *p, t_var **var)
{
	char	**al;
	int		i;

	i = 0;
	al = NULL;
	if (p->cmd[1])
		return (setenv_through_cmd_passed(p, var, al, i));
	return (-1);
}
