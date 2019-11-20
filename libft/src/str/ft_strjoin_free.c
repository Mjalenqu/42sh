/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin_free.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/02 11:16:43 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

void	ft_strjoin_free(char **s1, const char *s2)
{
	char *ret;

	if (!(ret = ft_malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1))))
	{
		ft_strdel(s1);
		return ;
	}
	ret[0] = '\0';
	ret = ft_strcat(ret, *s1);
	ret = ft_strcat(ret, (char *)s2);
	ft_strdel(s1);
	*s1 = ret;
}
