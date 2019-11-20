/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/02 11:03:25 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		l_s1;
	int		l_s2;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup((char*)s1));
	if (!s1 && s2)
		return (ft_strdup((char*)s2));
	l_s1 = ft_strlen(s1);
	l_s2 = ft_strlen(s2);
	str = NULL;
	if ((str = (char *)ft_malloc(sizeof(char) * ((l_s1 + l_s2) + 1))) == NULL)
		return (NULL);
	l_s1 = 0;
	while (s1[l_s1])
		str[i++] = s1[l_s1++];
	l_s2 = 0;
	while (s2[l_s2])
		str[i++] = s2[l_s2++];
	str[i] = '\0';
	return (str);
}
