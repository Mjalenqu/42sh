/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   back_slash_tools.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 18:13:32 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 16:06:13 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		check_quote_double(char *str, int *i, int *quote_double)
{
	if (str[*i + 1] == '"')
	{
		(*quote_double) = 0;
		(*i)++;
	}
	else
		(*quote_double) = (*quote_double == 1) ? 0 : 1;
	if (str[*i] && str[*i + 1] && (str[*i + 1] != '"' && str[*i + 1] != '\''))
		(*i)++;
}

void		check_quote_simple(char *str, int *i, int *quote_simple)
{
	if (str[*i + 1] == '\'')
	{
		(*quote_simple) = 0;
		(*i)++;
	}
	else
		(*quote_simple) = (*quote_simple == 1) ? 0 : 1;
	if (str[*i] && str[*i + 1] && (str[*i + 1] != '"' && str[*i + 1] != '\''))
		(*i)++;
}

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

void		solve_quote_simple(char *str, char **res, int *i, int j)
{
	if (str[*i] == '\'')
	{
		while (str[*i] && str[*i] == '\'')
			(*i)++;
	}
	if (str[*i])
		(*res)[j] = str[*i];
}
