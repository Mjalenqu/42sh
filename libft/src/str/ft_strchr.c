/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 16:16:49 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 13:13:53 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char		*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str_s;

	i = -1;
	str_s = (char*)s;
	while (str_s[++i] != '\0')
	{
		if (str_s[i] == (char)c)
			return (&str_s[i]);
	}
	if (c == 0 && s)
		return (&str_s[ft_strlen(s)]);
	return (NULL);
}
