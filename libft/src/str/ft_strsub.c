/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/08 17:49:02 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/08 17:51:09 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	i = start;
	j = 0;
	k = 0;
	if (s == NULL)
		return (NULL);
	if (!(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	while (s[i] && k++ < len)
	{
		str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}
