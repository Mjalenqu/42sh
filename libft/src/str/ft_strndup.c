/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strndup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 12:30:24 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 15:09:54 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char		*ft_strndup(char *s1, int n)
{
	int		i;
	char	*tab;

	i = ft_strlen(s1);
	if (n < i)
		i = n;
	if (!(tab = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
