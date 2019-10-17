/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncmp_case_unsensitive.c                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 10:32:07 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/16 10:38:40 by rlegendr    ###    #+. /#+    ###.fr     */
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

int				ft_strncmp_case_unsensitive(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (static_is_the_same_letter_unsensitive(s1[i], s2[i]) && i < n &&
		s1[i] && s2[i])
		i++;
	if (s1[i] != s2[i] && i < n)
		return (s1[i] - s2[i]);
	return (0);
}
