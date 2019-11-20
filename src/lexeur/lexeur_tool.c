/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexeur_tool.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/21 17:24:10 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 13:45:54 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

char		*get_fd_in(char *str)
{
	char	*fd_in;
	int		i;

	i = 0;
	while (str[i] && (str[i] != '<' && str[i] != '>'))
		i++;
	if (i != 0)
		fd_in = ft_strsub(str, 0, i);
	else
		fd_in = NULL;
	return (fd_in);
}

char		*get_fd_out(char *str)
{
	char	*fd_out;
	int		i;
	int		start;

	i = 0;
	while (str[i] && (str[i] != '&'))
		i++;
	i++;
	jump_space(str, &i);
	start = i;
	while (str[i] && (!odd_backslash(i - 1, str) && find_token(str, i) == -1))
		i++;
	fd_out = ft_strsub(str, start, i - start);
	return (fd_out);
}

void		fill_struct_fd_in(t_lexeur *res, char *fd_in, enum e_token token,
char *red)
{
	res->word = NULL;
	res->token = token;
	if (red)
		res->redirection = ft_strdup(red);
	else
		res->redirection = NULL;
	if (fd_in)
		res->fd_in = ft_strdup(fd_in);
	else
		res->fd_in = NULL;
	res->fd_out = NULL;
	ft_strdel(&red);
	ft_strdel(&fd_in);
}

void		fill_struct_fd_out(t_lexeur *res, char *fd_in, enum e_token token,
char *fd_out)
{
	res->word = NULL;
	res->token = token;
	res->redirection = NULL;
	if (fd_in)
		res->fd_in = ft_strdup(fd_in);
	else
		res->fd_in = NULL;
	if (fd_out)
		res->fd_out = ft_strdup(fd_out);
	else
		res->fd_out = NULL;
	ft_strdel(&fd_in);
	ft_strdel(&fd_out);
}

char		*ft_del_simple_quote(char *word)
{
	int		i;
	char	*res;

	i = 1;
	if (word[0] == '\'')
	{
		while (word[i] && word[i] != '\'')
			i++;
		res = ft_strsub(word, 1, i - 1);
	}
	else
		res = ft_strdup(word);
	return (res);
}
