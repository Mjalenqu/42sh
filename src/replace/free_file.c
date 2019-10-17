/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_file.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 18:04:12 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/18 18:04:29 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/alias.h"
#include "../../includes/lexeur.h"

void		free_list_tvar(t_tvar *alias)
{
	t_tvar		*tmp;

	while (alias)
	{
		ft_strdel(&alias->data);
		tmp = alias;
		alias = alias->next;
		free(tmp);
	}
}

void		free_list(t_alias *alias)
{
	t_alias		*tmp;

	while (alias)
	{
		ft_strdel(&alias->data);
		if (alias->prev)
			free(alias->prev);
		tmp = alias;
		alias = alias->next;
		free(tmp);
	}
}

void		free_ar(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_strdel(&str[i]);
		i++;
	}
	free(str);
}
