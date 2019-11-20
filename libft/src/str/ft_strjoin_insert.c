/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin_insert.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/02 17:13:45 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

void	ft_strjoin_insert(char **s1, char *s2, int i)
{
	char	*ret;
	int		j;

	ret = ft_strnew(ft_strlen(*s1) + ft_strlen(s2));
	j = 0;
	if (ret != NULL)
	{
		while ((*s1)[j] && j < i)
		{
			ret[j] = (*s1)[j];
			j++;
		}
		ret = ft_strcat(ret, s2);
		if ((*s1)[j])
		{
			ret = ft_strcat(ret, (*s1) + j);
		}
		ft_strdel(s1);
		*s1 = ret;
	}
	else
		ft_strdel(s1);
}
