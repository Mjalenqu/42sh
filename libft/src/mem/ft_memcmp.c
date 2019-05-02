/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/23 16:26:04 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 16:26:20 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_mem.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*s3;
	char	*s4;

	i = 0;
	s3 = (char *)s1;
	s4 = (char *)s2;
	while (i < n)
	{
		if (s3[i] != s4[i])
			return ((unsigned char)s3[i] - (unsigned char)s4[i]);
		i++;
	}
	return (0);
}
