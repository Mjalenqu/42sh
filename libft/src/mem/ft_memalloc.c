/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/23 16:11:31 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 16:13:19 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_mem.h"

void		*ft_memalloc(size_t size)
{
	void	*mem;

	if (size == 0 || (mem = malloc(size)) == NULL)
		return (NULL);
	mem = ft_memset(mem, '\0', size);
	return (mem);
}
