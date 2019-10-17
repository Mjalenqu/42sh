/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_lexeur_tool.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 21:05:25 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 21:06:58 by mdelarbr    ###    #+. /#+    ###.fr     */
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
	res = malloc(sizeof(char) * (ft_strlen(buf) + 1));
	while (buf[i])
	{
		if (buf[i] == '\\' && buf[i + 1])
			i++;
		res[j] = buf[i];
		if (buf[i])
			i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}
