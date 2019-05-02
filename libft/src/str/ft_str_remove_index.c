/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str_remove_index.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/09 13:43:28 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 13:07:27 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strrmvi(char *str, int i)
{
	char	*ret;

	ret = NULL;
	if (i < 0)
		ret = ft_strdup(str);
	else
	{
		ret = ft_strsub(str, 0, i);
		if (i + 1 < ft_strlen((const char *)str))
			ft_strjoin_free(&ret, str + i + 1);
	}
	ft_strdel(&str);
	return (ret);
}
