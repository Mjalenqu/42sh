/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrev.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/12 08:19:46 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 13:13:53 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char		*ft_strrev(char *str)
{
	int		i;
	int		len;
	int		len_less;
	char	tmp;

	len = 0;
	while (str[len])
		len++;
	i = 0;
	len_less = len - 1;
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len_less];
		str[len_less] = tmp;
		i++;
		len_less--;
	}
	return (str);
}
