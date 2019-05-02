/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/23 13:37:06 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 13:40:20 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

void	*ft_memset(void *b, int c, size_t l)
{
	size_t			i;
	unsigned char	*r;
	char			d;

	i = 0;
	d = (unsigned char)c;
	r = (unsigned char*)b;
	while (i < l)
	{
		r[i] = c;
		i++;
	}
	return (b);
}
