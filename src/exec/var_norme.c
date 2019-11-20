/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var_norme.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:11:03 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void		add_env_temp(t_var **var, char *str, int type)
{
	t_var	*start;
	t_var	*tmp;
	char	*name;

	name = init_name(str);
	start = (*var);
	if (check_name(name) == 1)
	{
		ft_strdel(&name);
		return ;
	}
	while ((*var)->next && (*var)->next->type == SPE)
		(*var) = (*var)->next;
	tmp = (*var)->next;
	(*var)->next = ft_malloc(sizeof(t_var));
	(*var)->next->name = name;
	(*var)->next->data = init_data(str);
	(*var)->next->type = type;
	(*var)->next->next = tmp;
	(*var) = start;
}

char		**remove_tab(char **src, int j)
{
	char	**res;
	int		i;
	int		k;
	int		len;

	i = 0;
	k = 0;
	len = 0;
	while (src[len])
		len++;
	if (len == 1)
		return (NULL);
	res = ft_malloc(sizeof(char*) * len);
	i = -1;
	while (src[++i])
	{
		if (i == j)
			i++;
		if (i > len)
			break ;
		res[k] = ft_strdup(src[i]);
		k++;
	}
	res[len - 1] = NULL;
	return (res);
}

t_var		*add_one(char *str, char *name)
{
	t_var *var;

	var = ft_malloc(sizeof(t_var));
	var->next = NULL;
	var->name = name;
	var->data = init_data(str);
	var->type = LOCAL;
	return (var);
}

int			add_env_check(char *name, t_var **var, char *str)
{
	if (check_name(name) == 1)
	{
		ft_printf_err("42sh: %s: ambiguous value name\n", name);
		ft_strdel(&name);
		return (1);
	}
	if (!(*var))
	{
		add_env_temp(var, str, LOCAL);
		stock(*var, 5);
		return (1);
	}
	return (0);
}
