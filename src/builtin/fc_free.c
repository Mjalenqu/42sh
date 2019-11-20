/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 07:42:30 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/11 13:25:53 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int			valid_heredocs(char *ans, int i, int open)
{
	while (ans[i])
	{
		if (open != -1 && (ans[i] == open ||
			(open == '$' && ans[i] == '}')) &&
			(odd_backslash(i - 1, ans) == 0 || ans[i] == 39))
			open = -1;
		else if (open == -1 &&
				(ans[i] == '"' || ans[i] == 39 ||
				(ans[i] == '$' && ans[i + 1] == '{')) &&
				(i == 0 || (i > 0 && odd_backslash(i - 1, ans) == 0)))
			open = ans[i];
		if (open == -1 && ans[i] == '<' && ans[i + 1] == '<' &&
				(i == 0 || (i > 0 && odd_backslash(i - 1, ans) == 0)))
			return (0);
		i++;
	}
	return (1);
}

int			get_value_of_cmd_return(t_fc fc, t_var *var)
{
	if (ft_strchr(fc.flags, 's') == NULL && ft_strchr(fc.flags, 'e') == NULL)
		return (0);
	while (var && ft_strcmp(var->name, "?") != 0)
		var = var->next;
	if (var && ft_strcmp(var->name, "?") == 0)
		return (ft_atoi(var->data));
	return (0);
}

void		free_fc_struct(t_fc *fc)
{
	ft_strdel(&fc->flags_model);
	ft_strdel(&fc->flags);
	ft_strdel(&fc->str_first);
	ft_strdel(&fc->str_last);
}
