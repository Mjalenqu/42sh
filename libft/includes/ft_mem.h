/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_mem.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/23 16:06:35 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 10:09:51 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_MEM_H
# define FT_MEM_H

# include <stdlib.h>
# include "ft_str.h"
# include "ft_unix.h"
# include "ft_int.h"
# include "ft_printf.h"
# include "ft_printf_err.h"

void	*ft_memset(void *mem, int c, size_t l);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_memdel(void **ap);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_free_void(void *ptr, void *ptr2, void *ptr3, void *ptr4);
void	ft_tabdel(char **tabl);

#endif
