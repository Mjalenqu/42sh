/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   back_slash_tools.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 18:13:32 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/18 18:13:47 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		cnt_solve_back_slash(char *buf, int *i, int *cnt)
{
	int		ret;

	(*cnt)++;
	while (buf[*i] && ((buf[*i] < 9 || buf[*i] > 13) &&
	buf[*i] != ' ' && buf[*i] != '"' && buf[*i] != '\''))
	{
		if ((ret = find_token(buf, *i)) != -1)
			if (buf[*i - 1] != '\\')
				break ;
		(*i)++;
	}
}

int			back_slash_count(char *str)
{
	int		a;
	int		i;

	a = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && str[i + 1] != '"'
		&& str[i + 1] != '\'')
			i++;
		a++;
		if (str[i])
			i++;
	}
	return (a);
}

int			del_back_slash_double_quote(int *k, int j, char ***ar)
{
	(*k)++;
	while ((*ar)[j][*k])
	{
		if ((*ar)[j][*k] == '"' && (*k == 0 ||
			(*ar)[j][*k - 1] != '\\'))
			return (1);
		(*k)++;
	}
	return (0);
}

int			del_back_slash_simple_quote(int *k, int j, char ***ar)
{
	(*k)++;
	while ((*ar)[j][*k])
	{
		if ((*ar)[j][*k] == '\'' && (*k == 0 ||
			(*ar)[j][*k - 1] != '\\'))
			return (1);
		(*k)++;
	}
	return (0);
}
