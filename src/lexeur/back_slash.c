/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   back_slash.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/27 16:12:36 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 20:58:59 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		fill_lex_solve_back_slash(char *buf, int *i, int *start)
{
	int		ret;

	*start = *i;
	while (buf[*i] && ((buf[*i] < 9 || buf[*i] > 13) &&
	(buf[*i] != ' ' && buf[*i] != '"' && buf[*i] != '\'')))
	{
		if ((ret = find_token(buf, *i)) != -1)
			if (buf[*i - 1] != '\\')
				break ;
		(*i)++;
	}
}

char		*solve_back_slash(char *str)
{
	char	*res;
	int		i;
	int		a;

	a = back_slash_count(str);
	res = malloc(sizeof(char) * (a + 1));
	a = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && str[i + 1] != '"'
		&& str[i + 1] != '\'')
			i++;
		res[a] = str[i];
		a++;
		i++;
	}
	res[a] = '\0';
	ft_strdel(&str);
	return (res);
}

int			del_back_slash_browse(char ***ar, int *j, int *k)
{
	int		token;

	if ((*ar)[*j][*k] == '\\' && ((*ar)[*j][*k + 1]) &&
	(token = find_token((*ar)[*j], *k + 1) != -1))
	{
		(*k) += g_fill_token[token].size + 1;
		return (1);
	}
	if ((*ar)[*j][*k] == '\'' && (*k == 0 || (*ar)[*j][*k - 1] != '\\'))
		if (del_back_slash_simple_quote(k, *j, ar))
			return (1);
	if ((*ar)[*j][*k] == '"' && (*k == 0 || (*ar)[*j][*k - 1] != '\\'))
		if (del_back_slash_double_quote(k, *j, ar))
			return (1);
	if ((*ar)[*j][*k] && (*ar)[*j][*k + 1] && (*ar)[*j][*k] == '\\')
	{
		if ((*ar)[*j][*k + 1] != '\'' && (*ar)[*j][*k + 1] != '"')
		{
			(*ar)[*j] = solve_back_slash((*ar)[*j]);
			return (1);
		}
	}
	(*k)++;
	return (0);
}

void		del_back_slash(char ***ar)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while ((*ar)[j])
	{
		while ((*ar)[j][k])
		{
			if (del_back_slash_browse(ar, &j, &k))
				break ;
			if (k > ft_strlen((*ar)[j]))
				k = ft_strlen((*ar)[j]);
		}
		k = 0;
		j++;
	}
}
