/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool_list.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 18:06:47 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 21:57:17 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		free_replace(t_replace *replace)
{
	t_replace	*tmp;

	tmp = NULL;
	while (replace)
	{
		ft_strdel(&replace->name);
		tmp = replace->next;
		free(replace);
		replace = tmp;
	}
}

void		init_replace(t_replace **replace)
{
	(*replace) = ft_malloc(sizeof(t_replace));
	(*replace)->name = NULL;
	(*replace)->next = NULL;
}

void		*get_replace(void *stock, int i)
{
	static t_replace *ret;

	if (i == 1)
		ret = stock;
	if (i == 2)
		return (ret);
	return (NULL);
}

char		*fill_res_token(int *tint, int ret, char *str)
{
	char	*res;
	int		s;
	char	*tmp;

	(tint[1])++;
	res = ft_strsub(str, (tint[0]), g_fill_token[ret].size);
	(tint[0]) += g_fill_token[ret].size;
	if (ret == 5 || ret == 8)
	{
		jump_space(str, &tint[0]);
		s = tint[0];
		while (str[tint[0]] && (str[tint[0]] < 9 || str[tint[0]] > 13)
		&& str[tint[0]] != ' ')
			tint[0]++;
		tmp = ft_strsub(str, s, tint[0] - s);
		ft_strjoin_free(&res, tmp);
		ft_strdel(&tmp);
	}
	return (res);
}

int			basic_split_init(char *str, int *tint, int *start, int *ret)
{
	while (str[tint[0]] && ((str[tint[0]] >= 9 && str[tint[0]] <= 13)
	|| str[tint[0]] == ' '))
		(tint[0])++;
	if (!str[tint[0]])
		return (-1);
	(*start) = tint[0];
	(*ret) = find_token(str, tint[0]);
	return (0);
}
