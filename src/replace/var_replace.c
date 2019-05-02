/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var_replace.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 17:44:11 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 19:39:44 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/termcaps.h"

char		*check_var_alias(t_var *env, char *str)
{
	t_var	*start;
	char	*tmp;

	start = env;
	while (start)
	{
		if ((ft_strcmp(start->name, str) == 0) && start->type != ENVIRONEMENT)
		{
			ft_strdel(&str);
			return (start->data);
		}
		start = start->next;
	}
	tmp = ft_strdup(str);
	ft_strdel(&str);
	return (tmp);
}

int			f_check_var_alias(t_var *env, char *str)
{
	t_var	*start;

	start = env;
	while (start)
	{
		if ((ft_strcmp(start->name, str) == 0) && start->type != ENVIRONEMENT)
			return (1);
		start = start->next;
	}
	return (0);
}
