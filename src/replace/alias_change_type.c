/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias_change_type.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 18:02:37 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/07 15:54:04 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/alias.h"

char		**make_list_to_ar(t_alias *alias)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (cnt_list(alias) + 1));
	i = 0;
	while (alias)
	{
		res[i] = ft_strdup(alias->data);
		i++;
		alias = alias->next;
	}
	res[i] = NULL;
	free_list(alias);
	return (res);
}

void		make_ar_to_list_while(int *i, char **str, t_alias **alias,
t_alias *prev)
{
	if (!(*alias))
		(*alias) = malloc(sizeof(t_alias));
	if (*i == 0)
		(*alias)->prev = NULL;
	else
		(*alias)->prev = prev;
	(*alias)->data = ft_strdup(str[*i]);
	prev = (*alias);
	if (str[*i + 1])
	{
		(*alias)->next = malloc(sizeof(t_alias));
		(*alias) = (*alias)->next;
	}
	(*i)++;
}

t_alias		*make_ar_to_list(char **str)
{
	t_alias		*start;
	t_alias		*alias;
	t_alias		*prev;
	int			i;

	if (!str || !(str[0]))
		return (NULL);
	alias = malloc(sizeof(t_alias));
	prev = NULL;
	start = alias;
	i = 0;
	while (str[i])
		make_ar_to_list_while(&i, str, &alias, prev);
	alias->next = NULL;
	alias = start;
	free_ar(str);
	return (start);
}

int			check_simple_or_multiple(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		while (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '))
			i++;
		j = i;
		while (str[j] && ((str[j] >= 9 && str[j] <= 13) || str[j] == ' '))
			j++;
		if (!str[j])
			return (0);
		return (1);
	}
	return (1);
}

char		*del_space(char *str)
{
	int		i;
	int		s;
	char	*tmp;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		jump_space(str, &i);
		s = i;
		while (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '))
			i++;
		tmp = ft_strsub(str, s, i - s);
		ft_strjoin_free(&res, tmp);
		ft_strdel(&tmp);
		if (str[i])
			i++;
	}
	ft_strdel(&str);
	return (res);
}
