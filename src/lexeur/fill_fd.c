/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_fd.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/02 09:44:19 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 18:22:38 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

t_lexeur	*fill_fd(char *red, int fd, int token)
{
	t_lexeur	*res;

	res = malloc(sizeof(t_lexeur));
	res->word = NULL;
	res->token = token;
	res->fd = fd;
	if (red)
		res->redirection = ft_strdup(red);
	else
		res->redirection = NULL;
	ft_strdel(&red);
	return (res);
}

t_lexeur	*fill_number(char *word, int token)
{
	t_lexeur	*res;

	res = malloc(sizeof(t_lexeur));
	if (word)
		res->word = ft_strdup(word);
	else
		res->word = NULL;
	res->token = token;
	res->fd = -1;
	res->redirection = NULL;
	ft_strdel(&word);
	return (res);
}

int			check_fd(char *buf, int i)
{
	int		token;

	while (buf[i] && (buf[i] >= '0' && buf[i] <= '9'))
		i++;
	if (!buf[i])
		return (1);
	token = find_token(buf, i);
	if (token != 4 && token != 5 && token != 6 && token != 7)
		return (1);
	return (0);
}

t_lexeur	*find_fd(char *buf, int *i)
{
	int			fd;
	char		*tmp;
	int			start;
	int			token;
	int			j;

	tmp = 0;
	j = *i;
	if (check_fd(buf, *i))
		return (NULL);
	if (buf[j] && (buf[j] >= '0' && buf[j] <= '9'))
	{
		start = j;
		while (buf[j] && (buf[j] >= '0' && buf[j] <= '9'))
			j++;
		token = find_token(buf, j);
		tmp = ft_strsub(buf, start, j - start);
		(*i) += ft_strlen(tmp);
		if (token != 4 && token != 5 && token != 6 && token != 7)
			return (fill_number(tmp, token));
		fd = ft_atoi(tmp);
		return (fill_fd(fill_redirection(buf, i, token), fd, token));
	}
	return (NULL);
}
