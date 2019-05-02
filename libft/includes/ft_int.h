/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_int.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/03 15:18:39 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 13:05:41 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_INT_H
# define FT_INT_H

# include <unistd.h>
# include <stdlib.h>
# include "ft_str.h"

int		ft_atoi(const char *str);
int		ft_int_len_base(int n, int base);
int		ft_isdigit(int n);
int		ft_isxdigit(int n);
void	ft_putnbr(int n);
void	ft_putnbr_base(int n, int base);
void	*ft_voidrev(void *s);
void	ft_voidswap(void *s, void *d);
char	*ft_itoa_base_uns(unsigned long long nb, int base);
size_t	check_num_length(long long nb);
#endif
