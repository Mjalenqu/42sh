/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_lexeur_tool.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 21:05:25 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 19:07:07 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

char		*change_buf(char *buf)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_malloc(sizeof(char) * (ft_strlen(buf) + 1));
	while (buf[i])
	{
		if (!odd_backslash(i, buf) && buf[i + 1])
			i++;
		res[j] = buf[i];
		if (buf[i])
			i++;
		j++;
	}
	res[j] = '\0';
	ft_strdel(&buf);
	return (res);
}
