/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/14 17:50:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 10:04:14 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

int			replace_alias_first_part(t_var **s_var, t_alias *alias,
t_replace *replace)
{
	while ((*s_var) && (ft_strcmp(alias->data, (*s_var)->name) != 0 ||
	(*s_var)->type != ALIAS))
		(*s_var) = (*s_var)->next;
	if (!(*s_var))
		return (0);
	while (replace->next)
		replace = replace->next;
	replace->next = ft_malloc(sizeof(t_replace));
	replace = replace->next;
	replace->name = ft_strdup(alias->data);
	replace->next = NULL;
	return (1);
}

int			replace_alias_last_part(t_alias *alias, int *ret, t_var *var,
t_replace *replace)
{
	if (alias->next && check_last_char(alias, (*ret)) == ' ')
	{
		while ((*ret) - 1)
		{
			alias = alias->next;
			(*ret)--;
		}
	}
	else if (replace_alias_first_part(&var, alias, replace) == 1)
		return (1);
	else
		return (0);
	return (1);
}

int			check_tok(t_alias *alias, t_var *var, t_replace *replace)
{
	t_alias *tmp;

	tmp = alias;
	while (tmp)
	{
		if (tmp && tmp->next && (ft_strcmp(tmp->data, "&&") == 0 ||
		ft_strcmp(tmp->data, "||") == 0
		|| ft_strcmp(tmp->data, ";") == 0 || ft_strcmp(tmp->data, "|") == 0))
			return (replace_alias(tmp->next, var, replace));
		tmp = tmp->next;
	}
	return (1);
}

int			check_boucle(t_alias *alias, t_replace *replace)
{
	while (replace)
	{
		if (ft_strcmp(alias->data, replace->name) == 0)
			return (0);
		replace = replace->next;
	}
	return (1);
}

int			replace_alias(t_alias *alias, t_var *var, t_replace *replace)
{
	t_var		*s_var;
	t_alias		*tmp;
	int			ret;

	tmp = alias;
	while (1)
	{
		s_var = var;
		if (replace_alias_first_part(&s_var, alias, replace) == 0)
			break ;
		ret = replace_alias_while(s_var, alias);
		if (check_boucle(alias, replace) == 0)
		{
			del_all_backslash(tmp);
			return (1);
		}
		if (replace_alias_last_part(alias, &ret, var, replace) == 0)
			break ;
		if (alias->next)
			alias = alias->next;
	}
	del_all_backslash(tmp);
	return (0);
}
