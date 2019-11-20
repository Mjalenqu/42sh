/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   back_slash.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/27 16:12:36 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/31 16:35:59 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		init_value(int *quote_simple, int *quote_double)
{
	*quote_double = 0;
	*quote_simple = 0;
}

void		solve_quote_double(char *str, char **res, int *i, int j)
{
	if (str[*i] == '"')
	{
		while (str[*i] && str[*i] == '"')
			(*i)++;
	}
	if (odd_backslash(*i, str) && str[*i + 1] &&
	(str[*i + 1] == '\\' || str[*i + 1] == '"' || str[*i + 1] == '$'))
		(*i)++;
	if (str[*i])
		(*res)[j] = str[*i];
}

void		solve_normal(char *str, char **res, int *i, int j)
{
	if (odd_backslash(*i, str))
		(*i)++;
	(*res)[j] = str[*i];
}

char		*browse_back_slash_and_quote(char *str, int i, int j, char *res)
{
	int			quote_double;
	int			quote_simple;

	res = (char *)ft_malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_bzero(res, ft_strlen(str));
	init_value(&quote_simple, &quote_double);
	while (str[i])
	{
		if (!quote_simple && (!odd_backslash(i - 1, str) && str[i] == '"'))
			check_quote_double(str, &i, &quote_double);
		if (!quote_double && ((quote_simple && str[i] == '\'') ||
		(!odd_backslash(i - 1, str) && str[i] == '\'')))
			check_quote_simple(str, &i, &quote_simple);
		if (quote_simple)
			solve_quote_simple(str, &res, &i, j);
		else if (quote_double)
			solve_quote_double(str, &res, &i, j);
		else if (str[i] && str[i] != '"' && str[i] != '\'')
			solve_normal(str, &res, &i, j);
		i += (str[i]) ? 1 : 0;
		j += (res[j]) ? 1 : 0;
	}
	res[j] = '\0';
	return (res);
}

char		**del_back_slash_and_quote(char **ar)
{
	int		i;
	char	**res;

	i = 0;
	while (ar[i])
		i++;
	res = (char **)ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ar[i])
	{
		res[i] = browse_back_slash_and_quote(ar[i], 0, 0, NULL);
		i++;
	}
	res[i] = NULL;
	ft_free_tab(ar);
	return (res);
}
