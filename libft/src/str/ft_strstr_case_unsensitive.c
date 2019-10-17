/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr_case_unsensitive.c                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 10:31:30 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/16 17:08:56 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

static int		static_is_the_same_letter_unsensitive(char a, char b)
{
	if ((a >= 65 && a <= 90 && a + 32 == b) ||
			(a >= 97 && a <= 122 && a - 32 == b) || a == b)
		return (1);
	return (0);
}

int				ft_strstr_case_unsensitive(char *str, char *tofind)
{
	int			j;
	int			i;
	char		*s;

	i = 0;
	s = str;
	if (tofind[0] == '\0')
		return (0);
	while (s[i])
	{
		j = 0;
		while (tofind[j] &&
			static_is_the_same_letter_unsensitive(s[i + j], (tofind[j])))
			j++;
		if (tofind[j] == '\0')
		{
			return (i + j);
		}
		i++;
	}
	return (-1);
}
