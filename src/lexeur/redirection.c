/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 17:01:39 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 20:02:12 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

char			*fill_redirection(char **buf, int *i)
{
	char	*res;

	if (buf[*i + 1])
	{
		(*i)++;
		res = ft_strdup(buf[*i]);
		return (res);
	}
	return (NULL);
}

char			*fill_redirection_heredoc(char **buf, int *i)
{
	int		s;
	int		j;

	j = 0;
	while (buf[*i][j] && find_token(buf[*i], j) == -1)
		j++;
	j += g_fill_token[7].size;
	jump_space(buf[*i], &j);
	s = j;
	while (buf[*i][j] && ((buf[*i][j] < 9 || buf[*i][j] > 13)
	&& buf[*i][j] != ' '))
		j++;
	return (ft_strsub(buf[*i], s, j - s));
}
