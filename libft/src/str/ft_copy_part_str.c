/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_copy_part_str.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/22 18:04:42 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 13:10:09 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char			*copy_beginning_str(char *str, int i)
{
	char		*dest;
	int			j;

	dest = NULL;
	j = 0;
	if (!(dest = (char*)malloc(sizeof(char) * i + 2)))
		return (NULL);
	while (j <= i)
	{
		dest[j] = str[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char			*copy_end_string(char *str, int i)
{
	char		*dest;
	int			j;

	dest = NULL;
	j = 0;
	if (!(dest = (char*)malloc(sizeof(char) * (ft_strlen(str) - i) + 1)))
		return (NULL);
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	return (dest);
}

char			*ft_copy_part_str(char *str, int i, int usage)
{
	char		*dest;

	dest = NULL;
	if (usage == 0)
		dest = copy_beginning_str(str, i);
	else if (usage == 1)
		dest = copy_end_string(str, i);
	return (dest);
}
