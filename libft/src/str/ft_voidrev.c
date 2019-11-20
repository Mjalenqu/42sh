/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_voidrev.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/03 15:04:31 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

void	*ft_voidrev(void *s)
{
	size_t		i;
	size_t		j;
	char		*c;

	i = 0;
	c = (char *)s;
	while (c[i])
		i++;
	j = 0;
	i--;
	while (i > j)
	{
		ft_voidswap(&c[i--], &c[j++]);
	}
	return (s);
}
