/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/03 13:14:38 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

static char	ft_inttochar(int i)
{
	if (i < 10)
		return (i + 48);
	else
		return ('A' + i - 10);
}

static int	ft_intlen_base(int n, int base)
{
	if (n < 0)
	{
		if (n / base)
			return (2 + ft_intlen_base(-(n / base), base));
		else
			return (1 + ft_intlen_base((n / base), base));
	}
	else if (n < base)
		return (1);
	return (1 + ft_intlen_base(n / base, base));
}

char		*ft_itoa_base(int nb, int base)
{
	char	*r;
	int		j;
	long	n;

	if (base <= 1)
		return (NULL);
	j = ft_intlen_base(nb, base);
	if (!(r = ft_malloc(sizeof(*r) * (j + 1))))
		return (NULL);
	r[j--] = '\0';
	n = nb;
	if (nb < 0)
		n = n * -1;
	while (j >= 0)
	{
		r[j] = ft_inttochar(n % base);
		n = n / base;
		j--;
	}
	if (nb < 0)
		r[0] = '-';
	return (r);
}
