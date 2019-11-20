/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_lexeur.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/27 11:29:05 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 13:45:17 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		jump_space(char *buf, int *i)
{
	while (buf[*i] && ((buf[*i] >= 9 && buf[*i] <= 13) || buf[*i] == ' '))
		(*i)++;
}

void		check_token_for_redirection_quote(char *str, int *i)
{
	if (str[*i] && str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	}
	if (str[*i] && str[*i] == '"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '"')
			(*i)++;
	}
}

int			check_token_for_redirection(char *str)
{
	int		i;
	int		token;

	token = 0;
	i = 0;
	while (str[i])
	{
		check_token_for_redirection_quote(str, &i);
		if (!odd_backslash(i - 1, str))
			token = find_token(str, i);
		if (token == 4 || token == 6 || token == 7 ||
		token == 9 || token == 5 || token == 8)
			return (token);
		if (str[i])
			i++;
	}
	return (-1);
}

void		fill_lex_exist(char **buf, int *i, int *j, t_lexeur **array)
{
	int		token;
	int		k;

	k = 0;
	token = check_token_for_redirection(buf[*i]);
	if (token == 7)
		fill_lex_heredoc(&array, j, buf, i);
	else if (token != -1)
		array[*j] = fill_lex_redirection(buf, i, token);
	else
		array[*j] = fill_lex_while(&buf[*i], i, find_token(buf[*i], k));
	(*j)++;
}

t_lexeur	**fill_lex(char **buf, t_lexeur **array)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (buf[i])
		i++;
	array = ft_malloc(sizeof(t_lexeur *) * (i + 1));
	i = 0;
	while (buf[i])
	{
		if (!(ft_strcmp(buf[i], "")))
			i++;
		if (buf[i])
			fill_lex_exist(buf, &i, &j, array);
	}
	array[j] = NULL;
	return (array);
}
