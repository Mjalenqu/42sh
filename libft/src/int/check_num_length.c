/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_num_length.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 10:29:54 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 12:58:22 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_int.h"

size_t			check_num_length(long long nb)
{
	size_t		length;

	length = 0;
	while (nb >= 1 || nb <= -1)
	{
		nb = nb / 10;
		length++;
	}
	if (length == 0)
		return (1);
	return (length);
}
