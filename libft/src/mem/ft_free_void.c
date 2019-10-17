/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_voids.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/22 12:45:00 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/16 12:57:28 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_mem.h"

void	ft_free_void(void *ptr, void *ptr2, void *ptr3, void *ptr4)
{
	if (ptr)
		free(ptr);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	if (ptr4)
		free(ptr4);
}
