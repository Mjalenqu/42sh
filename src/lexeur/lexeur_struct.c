/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexeur_struct.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/21 17:38:30 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/26 13:34:12 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		fill_struct(t_lexeur *res, char *word, enum e_token token,
char *red)
{
	res->word = ft_strdup(word);
	res->token = token;
	res->redirection = NULL;
	res->fd_in = NULL;
	res->fd_out = NULL;
	ft_strdel(&red);
}

t_lexeur	*fill_lex_while(char **buf, int *i, int token)
{
	t_lexeur	*res;

	if (odd_backslash(0, *buf) && find_token((*buf), 1) != -1)
		*buf = change_buf(*buf);
	res = ft_malloc(sizeof(t_lexeur));
	if (token == -1)
		fill_struct(res, *buf, token, NULL);
	else
		fill_struct(res, NULL, token, NULL);
	(*i)++;
	return (res);
}

void		fill_lex_heredoc(t_lexeur ***array, int *j, char **buf, int *i)
{
	char		*tag;

	(*array)[*j] = ft_malloc(sizeof(t_lexeur));
	fill_struct_fd_in((*array)[*j], get_fd_in(buf[*i]), 7,
	fill_redirection_heredoc(buf, i));
	tag = ft_strdup((*array)[*j]->redirection);
	(*i)++;
	while (buf[*i])
	{
		(*j)++;
		(*array)[*j] = ft_malloc(sizeof(t_lexeur));
		fill_struct((*array)[*j], buf[*i], -1, NULL);
		if (!ft_strcmp(buf[*i], tag))
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	ft_strdel(&tag);
}

t_lexeur	*fill_lex_redirection(char **buf,
int *i, enum e_token token)
{
	t_lexeur *res;

	res = ft_malloc(sizeof(t_lexeur));
	if (token == 4 || token == 6 || token == 9 || token == 7)
	{
		fill_struct_fd_in(res, get_fd_in(buf[*i]), token,
		fill_redirection(buf, i));
		if (res->redirection)
			(*i)++;
		return (res);
	}
	if (token == 5 || token == 8)
	{
		fill_struct_fd_out(res, get_fd_in(buf[*i]), token,
		get_fd_out(buf[*i]));
		(*i)++;
		return (res);
	}
	return (NULL);
}

void		token_8_and_5(int *i, int ret, char *str)
{
	(*i) += g_fill_token[ret].size;
	if (str[*i + 1])
		(*i)++;
	while (str[*i] && (str[*i] < 9 || str[*i] > 13) && str[*i] != ' '
	&& (find_token(str, *i) == -1))
		(*i)++;
}
