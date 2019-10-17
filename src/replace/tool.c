/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tool.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/09 10:52:26 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 11:12:22 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

char	*get_tag(char *str, int *i)
{
	int		s;
	int		j;
	int		ret;
	char	*tag;

	while (str[*i] && (ret = find_token(str, *i)) != 7)
		(*i)++;
	(*i) += g_fill_token[ret].size;
	j = (*i);
	jump_space(str, &j);
	s = j;
	while (str[j] && ((str[j] < 9 || str[j] > 13) && str[j] != ' '))
		j++;
	tag = ft_strsub(str, s, j - s);
	return (tag);
}

int		check_int_for_heredoc(char *str, int i)
{
	if (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		while (str[i] && (str[i] >= '0' && str[i] <= '9'))
			i++;
		if (find_token(str, i) == 7)
			return (1);
	}
	return (0);
}

int		basic_split_while(int *tint, char *str, char **res, char **tag)
{
	int		start;
	int		ret;

	if (basic_split_init(str, tint, &start, &ret) == -1)
		return (-1);
	if (tint[2] && tag != NULL)
		heredoc_go_next(str, &tint[0], (*tag), &tint[2]);
	if (ret == 7 || check_int_for_heredoc(str, tint[0]))
	{
		ft_strdel(tag);
		(*tag) = get_tag(str, &tint[0]);
		tint[2] = 1;
	}
	else if (str[tint[0]] && ((str[tint[0]] >= '0' && str[tint[0]] <= '9') ||
	(ret == 5 || ret == 8)))
		split_space_find_number(str, &tint[0]);
	else if (search_agregator(str, tint[0]))
		split_agregator(str, &tint[0]);
	else
		split_space_basic(str, &tint[0]);
	res[tint[1]] = ft_strsub(str, start, (tint[0]) - start);
	if (str[tint[0]] && (ret = find_token(str, tint[0])) != -1)
		res[tint[1]] = fill_res_token(tint, ret, str);
	return (1);
}

char	**split_space(char *str)
{
	int		tint[3];
	char	**res;
	char	*tag;

	tint[0] = 0;
	tint[1] = 0;
	tint[2] = 0;
	tag = NULL;
	res = malloc(sizeof(char *) * (ft_strlen(str) + 2));
	while (str[tint[0]])
	{
		if (basic_split_while(tint, str, res, &tag) == 1)
			tint[1]++;
	}
	res[tint[1]] = NULL;
	ft_strdel(&tag);
	return (res);
}

void	list_add(t_replace **replace, char *array)
{
	t_replace	*next;
	t_replace	*start;

	start = (*replace);
	while ((*replace)->next)
		(*replace) = (*replace)->next;
	next = malloc(sizeof(t_replace));
	next->name = ft_strdup(array);
	next->next = NULL;
	(*replace)->next = next;
	(*replace) = start;
}
