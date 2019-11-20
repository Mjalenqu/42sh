/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env_replace.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 17:41:43 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/23 12:50:23 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/termcaps.h"

char		*switch_word(char *str, char *tmp, int i)
{
	char	*res;
	int		j;
	int		k;

	j = 0;
	while (j < i)
		j++;
	res = ft_strsub(str, 0, j);
	if (ft_strcmp(tmp, "") == 0)
		return (res);
	ft_strjoin_free(&res, tmp);
	k = j;
	while (str[k] && ((str[k] < 9 && str[k] > 13) || str[k] != ' '))
		k++;
	j = k;
	while (str[j])
		j++;
	ft_strjoin_free(&res, ft_strsub(str, k, j - k));
	ft_strdel(&str);
	return (res);
}

char		*replace_while(t_var *env, char *ar[4])
{
	t_var	*start;

	start = env;
	while (start)
	{
		if (ft_strcmp(ar[0], start->name) == 0 && start->type == ENVIRONEMENT)
		{
			ar[2] = ft_strjoin(ar[1], start->data);
			ft_strjoin_free(&ar[2], ar[3]);
			ft_strdel(&ar[0]);
			ft_strdel(&ar[1]);
			return (ar[2]);
		}
		start = start->next;
	}
	return (ft_strdup(ar[1]));
}

char		*replace_env(t_var *env, char *str, int i)
{
	int		s;
	char	*ar[5];

	s = i;
	ar[3] = ft_strdup("");
	while (str[i] && str[i] != '$')
		i++;
	ar[1] = ft_strsub(str, s, i - s);
	i++;
	s = i;
	while (str[i] && str[i] != '$' && str[i] != '"' &&
	(str[i] < 9 || str[i] > 13) && str[i] != ' ')
		i++;
	ar[0] = ft_strsub(str, s, i - s);
	if (str[i])
	{
		s = i;
		while (str[i])
			i++;
		ar[3] = ft_strsub(str, s, i - s);
	}
	ar[2] = replace_while(env, ar);
	ft_strdel(&ar[0]);
	ft_strdel(&ar[1]);
	return (ar[2]);
}
