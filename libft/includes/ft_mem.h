/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_mem.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/23 16:06:35 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 16:31:00 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_STR_H
# define FT_STR_H

#include <stdlib.h>

void				*ft_memset(void *mem, int c, size_t l);
void				*ft_memccpy(void *restrict dst, const void *restrict src,
					int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_memdel(void **ap);
void	*ft_memmove(void *dest, const void *src, size_t n);
#endif
