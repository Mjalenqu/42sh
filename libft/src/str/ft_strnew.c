/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/02 17:17:28 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/05 14:17:22 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strnew(int size)
{
	char	*str;

	if (!(str = malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	ft_bzero(str, size);
	str[size] = '\0';
	return (str);
}
