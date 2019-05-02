/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   back_slash.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/27 16:12:36 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 18:20:52 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		fill_lex_solve_back_slash(char *buf, int *i, int *start)
{
	int		ret;

	*start = *i;
	while (buf[*i] && ((buf[*i] < 9 || buf[*i] > 13) &&
	(buf[*i] != ' ')))
	{
		if ((ret = find_token(buf, *i)) != -1)
			if (buf[*i - 1] != '\\')
				break ;
		(*i)++;
	}
}

void		cnt_solve_back_slash(char *buf, int *i, int *cnt)
{
	int		ret;

	(*cnt)++;
	while (buf[*i] && ((buf[*i] < 9 || buf[*i] > 13) &&
	buf[*i] != ' '))
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
		if (str[i] == '\\')
			i++;
		a++;
		if (str[i])
			i++;
	}
	return (a);
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
		if (str[i] == '\\' && str[i + 1])
			i++;
		res[a] = str[i];
		a++;
		i++;
	}
	res[a] = '\0';
	ft_strdel(&str);
	return (res);
}

void		del_back_slash(t_lexeur ***array)
{
	int		j;
	int		k;
	int		start;

	j = 0;
	k = 0;
	start = 0;
	while ((*array)[j])
	{
		if ((*array)[j]->word != NULL)
		{
			while ((*array)[j]->word[k])
			{
				if ((*array)[j]->word[k + 1] && (*array)[j]->word[k] == '\\')
				{
					(*array)[j]->word = solve_back_slash((*array)[j]->word);
					break ;
				}
				k++;
			}
		}
		k = 0;
		j++;
	}
}
