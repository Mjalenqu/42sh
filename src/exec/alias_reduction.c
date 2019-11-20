/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias_reduction.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 10:28:45 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

int		print_alias(t_var *var)
{
	while (var)
	{
		if (var->type == ALIAS)
			ft_printf_fd("%s=%s\n", var->name, var->data);
		var = var->next;
	}
	return (0);
}

int		check_name(char *name)
{
	if ((ft_strcmp(name, "_") == 0) || (ft_strcmp(name, "?") == 0) ||
	(ft_strcmp(name, "!") == 0) || (ft_strcmp(name, "$") == 0) ||
	(ft_strcmp(name, "0") == 0) || ft_isalnum_underscore(name) == 1)
		return (1);
	return (0);
}

int		print_err(char *name, char *data)
{
	ft_printf_err_fd("42sh: alias: error: Permission denied\n");
	ft_strdel(&name);
	ft_strdel(&data);
	return (1);
}

void	ft_free_deux(char *s, char *s1)
{
	ft_strdel(&s);
	ft_strdel(&s1);
}

int		error_unlias(char *str)
{
	ft_printf_err_fd("42sh: unalias: %s: not found\n", str);
	return (1);
}
