/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/03 15:04:04 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strstr(const char *str, const char *tofind)
{
	int		j;
	char	*s;

	s = (char*)str;
	if (tofind[0] == '\0')
		return (s);
	while (*s)
	{
		j = 0;
		while (*(s + j) == tofind[j] && tofind[j])
			j++;
		if (tofind[j] == '\0')
			return (s);
		s++;
	}
	return (NULL);
}
