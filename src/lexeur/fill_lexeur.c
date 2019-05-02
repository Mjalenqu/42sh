/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_lexeur.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/27 11:29:05 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/24 16:08:02 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		jump_space(char *buf, int *i)
{
	while (buf[*i] && ((buf[*i] >= 9 && buf[*i] <= 13) || buf[*i] == ' '))
		(*i)++;
}

void		fill_struct(t_lexeur *res, char *word, enum e_token token,
char *red)
{
	if (word)
		res->word = ft_strdup(word);
	else
		res->word = NULL;
	res->token = token;
	if (red)
		res->redirection = ft_strdup(red);
	else
		res->redirection = NULL;
	res->fd = -1;
	ft_strdel(&word);
	ft_strdel(&red);
}

t_lexeur	*fill_lex_redirection(char *buf, t_lexeur *res, int *i, int token)
{
	if (token == 4 || token == 5 || token == 6 || token == 7)
	{
		fill_struct(res, NULL, token, fill_redirection(buf, i, token));
		return (res);
	}
	fill_struct(res, NULL, token, NULL);
	*i += g_fill_token[token].size;
	return (res);
}

t_lexeur	*fill_lex_while(char *buf, int *i, int token)
{
	t_lexeur	*res;
	int			start;

	res = malloc(sizeof(t_lexeur));
	if (buf[*i] && token != -1)
		return (fill_lex_redirection(buf, res, i, token));
	else if (buf[*i] && ((buf[*i] >= 9 && buf[*i] <= 13) || buf[*i] == ' '))
		jump_space(buf, i);
	else if (buf[*i] && ((buf[*i] < 9 || buf[*i] > 13) && (buf[*i] != ' ')))
	{
		fill_lex_solve_back_slash(buf, i, &start);
		fill_struct(res, ft_strsub(buf, start, *i - start), -1, NULL);
		return (res);
	}
	else
		(*i)++;
	return (NULL);
}

t_lexeur	**fill_lex(char *buf, t_lexeur **array)
{
	int			i;
	int			j;
	t_lexeur	*tmp;

	i = 0;
	j = 0;
	array = malloc(sizeof(t_lexeur *) * (cnt_wrd(buf) + 1));
	while (buf[i])
	{
		jump_space(buf, &i);
		if (!buf[i])
			break ;
		if ((tmp = find_fd(buf, &i)) != NULL)
			array[j] = tmp;
		else
			array[j] = fill_lex_while(buf, &i, find_token(buf, i));
		j++;
	}
	array[j] = NULL;
	check_redirection(&array);
	del_back_slash(&array);
	return (array);
}
