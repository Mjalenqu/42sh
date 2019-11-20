/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/31 16:03:53 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/31 16:03:55 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_mem.h"

void		*ft_memalloc(size_t size)
{
	void	*mem;

	if (size == 0 || (mem = ft_malloc(size)) == NULL)
		return (NULL);
	mem = ft_memset(mem, '\0', size);
	return (mem);
}
