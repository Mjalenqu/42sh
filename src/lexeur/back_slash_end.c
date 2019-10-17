/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   back_slash_end.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 18:12:52 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 16:37:20 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

int			back_slash_count_end(char *str)
{
	int		a;
	int		i;

	a = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && str[i + 1] != '"'
		&& str[i + 1] != '\'' && str[i + 1] != '$' && str[i + 1] != ' ')
			i++;
		a++;
		if (str[i])
			i++;
	}
	return (a);
}

char		*solve_back_slash_end(char *str)
{
	char	*res;
	int		i;
	int		a;
	int		tmp;

	a = back_slash_count_end(str);
	res = malloc(sizeof(char) * (a + 2));
	tmp = a;
	a = 0;
	i = 0;
	while (str[i] && a <= tmp)
	{
		if (str[i] && (str[i] == '\\' && str[i + 1] && (str[i + 1] == '"'
		|| str[i + 1] == '\'' || str[i + 1] == '$')))
			i++;
		res[a] = str[i];
		a++;
		i++;
	}
	res[a] = '\0';
	ft_strdel(&str);
	return (res);
}

int			del_back_slash_end_browse(char ***ar, int j, int *k)
{
	if ((*ar)[j][*k + 1] && ((*ar)[j][*k + 1] == '\''
	|| (*ar)[j][*k + 1] == '"' || (*ar)[j][*k + 1] == '$')
	&& (*ar)[j][*k] == '\\')
	{
		(*ar)[j] = solve_back_slash_end((*ar)[j]);
		return (1);
	}
	(*k)++;
	return (0);
}

void		del_back_slash_end(char ***ar)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while ((*ar)[j])
	{
		while ((*ar)[j][k])
			if (del_back_slash_end_browse(ar, j, &k))
				break ;
		k = 0;
		j++;
	}
}
