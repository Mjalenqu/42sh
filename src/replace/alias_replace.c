/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias_replace.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/23 09:48:21 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/03 07:31:29 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

void		replace_alias_while_fill(char *tmp, int *j, int *i, t_alias *alias)
{
	int		t;
	int		s;

	s = *j;
	while (tmp[*j] && ((tmp[*j] < 9 || tmp[*j] > 13) && tmp[*j] != ' '))
		(*j)++;
	t = *j;
	while (tmp[t] && ((tmp[t] >= 9 && tmp[t] <= 13) || tmp[t] == ' '))
		t++;
	if (tmp[t])
		fill_alias_multiple(ft_strsub(tmp, s, (*j) - s), alias, i);
	else
		fill_alias_multiple(ft_strsub(tmp, s, t - s), alias, i);
}

int			replace_alias_while(t_var *var, t_alias *alias)
{
	char	*tmp;
	int		j;
	int		i;

	j = 0;
	i = 0;
	tmp = ft_strdup(var->data);
	if (!check_simple_or_multiple(tmp))
	{
		while (tmp[j])
			j++;
		fill_alias_solo(ft_strsub(tmp, 0, j), alias);
		ft_strdel(&tmp);
		return (1);
	}
	while (tmp[j])
	{
		replace_alias_while_fill(tmp, &j, &i, alias);
		jump_space(tmp, &j);
	}
	ft_strdel(&tmp);
	return (i);
}
