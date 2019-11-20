/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias_cnt.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 18:03:26 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/01 15:30:51 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

int			cnt_array(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			cnt_list(t_alias *alias)
{
	int		nb;

	nb = 0;
	while (alias)
	{
		alias = alias->next;
		nb++;
	}
	return (nb);
}

void		fill_alias_solo(char *str, t_alias *alias)
{
	char	*tmp;

	tmp = alias->data;
	alias->data = ft_strdup(str);
	ft_strdel(&tmp);
	ft_strdel(&str);
}

void		ft_add_list(t_alias *alias, int i, char *str)
{
	int		j;
	t_alias	*new;

	new = ft_malloc(sizeof(t_alias));
	new->data = ft_strdup(str);
	j = 0;
	while (j < i - 1)
	{
		alias = alias->next;
		j++;
	}
	new->next = alias->next;
	new->prev = alias;
	alias->next = new;
}

void		fill_alias_multiple(char *str, t_alias *alias, int *i)
{
	if (*i >= 1)
	{
		ft_add_list(alias, *i, str);
	}
	else
	{
		ft_strdel(&alias->data);
		alias->data = ft_strdup(str);
	}
	ft_strdel(&str);
	(*i)++;
}
