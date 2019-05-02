/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/02 11:03:25 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 17:54:14 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	char	*ret;

	i = 0;
	if (!(ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	ret[0] = '\0';
	ret = ft_strcat(ret, (char *)s1);
	ret = ft_strcat(ret, (char *)s2);
	return (ret);
}
