/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strfdup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 16:01:39 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 13:09:33 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strfdup(char *str)
{
	char	*ret;
	int		i;

	if (str == NULL)
		return (NULL);
	if (!(ret = ft_malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	ft_strdel(&str);
	return (ret);
}
