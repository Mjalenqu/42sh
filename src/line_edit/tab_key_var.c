/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key_var.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 14:15:31 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 13:03:00 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static char		*get_var_name(char *ans, int i, t_pos *pos)
{
	int		min;

	while (i > 1 && ans[i - 1] != '$')
		i -= 1;
	if (ans[i] == 0 || ans[i] == '$' || ans[i] == '&' || ans[i] == '|' ||
		ans[i] == ';' || ans[i] == 32)
		return (NULL);
	min = i;
	if (ans[i] == '{')
	{
		min += 1;
		pos->braceparam = 1;
	}
	while (ans[i] && ans[i] != '$' && ans[i] != '&' && ans[i] != '|' &&
		ans[i] != ';' && ans[i] != 32)
		i += 1;
	if (ans[i] == 0)
		return (ft_strdup(ans + min));
	return (ft_strndup(ans + min, i - min));
}

t_htab			*looking_for_var(t_pos *pos, t_htab *htab, char **name)
{
	t_var	*var;

	ft_strdel(name);
	*name = get_var_name(pos->ans, pos->let_nb, pos);
	var = stock(NULL, 6);
	while (var)
	{
		htab = add_list_back_htab(htab);
		htab->content = ft_strdup(var->name);
		htab->content_no = htab->prev == NULL ? 0 : htab->prev->content_no + 1;
		if (htab->prev == NULL)
			htab->lenght_max = ft_strlen(htab->content);
		else
			htab->lenght_max = htab->prev->lenght_max <
			ft_strlen(htab->content) ?
			ft_strlen(htab->content) : htab->prev->lenght_max;
		var = var->next;
	}
	if (htab)
	{
		htab = adjust_lenght_max(htab);
		htab = sort_list_htab(htab);
	}
	return (htab);
}
