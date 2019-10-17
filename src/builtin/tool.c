/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 15:27:39 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 08:33:55 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

int			ft_tabclen(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

char		*ft_get_val(char *name, t_var *var, int type)
{
	while (var)
	{
		if (ft_strcmp(name, var->name) == 0 && var->type == type)
			return (var->data);
		var = var->next;
	}
	return (NULL);
}

void		remove_item_var(t_var **var)
{
	free((*var)->name);
	free((*var)->data);
	free(*var);
	*var = NULL;
}

int			remove_list_var(t_var **ptr_var, int type, char *name)
{
	t_var *var;
	t_var *buf;
	t_var *pres;

	var = *ptr_var;
	if (ft_strcmp(name, (var)->name) == 0 && (var)->type == type)
	{
		buf = (*ptr_var)->next;
		remove_item_var(ptr_var);
		(*ptr_var) = buf;
		return (1);
	}
	while (var != NULL)
	{
		if (ft_strcmp(name, var->name) == 0 && var->type == type)
		{
			buf = var->next;
			remove_item_var(&var);
			pres->next = buf;
			return (1);
		}
		pres = var;
		var = var->next;
	}
	return (0);
}

void		free_name_and_data(char *name, char *data)
{
	ft_strdel(&name);
	ft_strdel(&data);
}
