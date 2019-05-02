/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putcolor2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 09:19:55 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 09:27:00 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

void	ft_putcolor2(char *s1, char *s2, char *s3, char *s4)
{
	write(1, s1, ft_strlen(s1));
	write(1, s2, ft_strlen(s2));
	write(1, s3, ft_strlen(s3));
	write(1, s4, ft_strlen(s4));
}
