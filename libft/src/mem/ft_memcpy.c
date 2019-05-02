/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/23 16:26:46 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 16:27:12 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_mem.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;
	char	*srcs;
	size_t	i;

	dest = (char *)dst;
	srcs = (char *)src;
	i = 0;
	while (i < n)
	{
		dest[i] = srcs[i];
		i++;
	}
	dst = (void*)dest;
	return (dst);
}
