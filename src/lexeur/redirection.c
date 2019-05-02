/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 17:01:39 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 18:22:10 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

char			*fill_redirection(char *buf, int *i, int token)
{
	char	*red;
	int		start;
	int		j;

	*i += g_fill_token[token].size;
	jump_space(buf, i);
	start = *i;
	if (token == 4 || token == 5)
	{
		while (buf[*i] && ((buf[*i] < 9 || buf[*i] > 13) && buf[*i] != ' '))
		{
			j = *i;
			if (find_token(buf, j) != -1)
				break ;
			(*i)++;
		}
		red = ft_strsub(buf, start, *i - start);
		return (red);
	}
	return (NULL);
}

t_lexeur		*fill_all(t_lexeur ***array, int j)
{
	t_lexeur	*res;

	res = malloc(sizeof(t_lexeur));
	if ((*array)[j]->redirection)
		res->redirection = ft_strdup((*array)[j]->redirection);
	else
		res->redirection = NULL;
	if ((*array)[j]->word)
		res->word = ft_strdup((*array)[j]->word);
	else
		res->word = NULL;
	res->token = (*array)[j]->token;
	res->fd = (*array)[j]->fd;
	return (res);
}

void			replace_input(t_lexeur ***array,
				t_lexeur ***res, int *i, int *j)
{
	if (!(*array)[0]->word)
	{
		(*res)[*j] = malloc(sizeof(t_lexeur));
		(*res)[*j]->token = (*array)[*i + 1]->token;
		(*res)[*j]->redirection = ft_strdup("");
		(*res)[*j]->word = NULL;
		(*res)[*j]->fd = (*array)[*i + 1]->fd;
		(*i)++;
	}
	else if ((*array)[*i + 1] && ((*array)[*i + 1]->token == 6
	|| (*array)[*i + 1]->token == 7))
	{
		(*res)[*j] = malloc(sizeof(t_lexeur));
		(*res)[*j]->token = (*array)[*i + 1]->token;
		(*res)[*j]->redirection = ft_strdup((*array)[*i]->word);
		(*res)[*j]->word = NULL;
		(*res)[*j]->fd = (*array)[*i + 1]->fd;
		(*i)++;
	}
	else
	{
		(*res)[*j] = (*array)[*i];
		(*res)[*j] = fill_all(array, *i);
	}
	(*i)++;
	(*j)++;
}

t_lexeur		**find_input_redirection(t_lexeur ***array)
{
	int			i;
	int			j;
	t_lexeur	**res;

	j = 0;
	i = 0;
	while ((*array)[j])
		j++;
	res = malloc(sizeof(t_lexeur *) * (j));
	j = 0;
	while ((*array)[i])
	{
		replace_input(array, &res, &i, &j);
	}
	res[j] = NULL;
	return (res);
}

t_lexeur		**check_redirection(t_lexeur ***array)
{
	int		j;

	j = 0;
	while ((*array)[j])
	{
		if ((*array)[j]->token == 6 || (*array)[j]->token == 7)
			return ((*array) = find_input_redirection(array));
		j++;
	}
	return ((*array));
}
