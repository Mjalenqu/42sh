/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str_remove_index.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/09 13:43:28 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:39 by mjalenqu    ###    #+. /#+    ###.fr     */
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
	return (ret);
}
