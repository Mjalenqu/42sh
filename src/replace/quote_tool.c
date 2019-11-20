/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quote_tool.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 20:06:15 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/18 14:22:30 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

int		check_red(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (find_token(str, i) != -1)
			return (0);
		i++;
	}
	return (1);
}

char	*remove_simple_quote(char **str)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\'')
		i++;
	tmp = ft_strrmvi((*str), i);
	ft_strdel(&(*str));
	i = 0;
	while (tmp[i] && tmp[i] != '\'')
		i++;
	(*str) = ft_strrmvi(tmp, i);
	ft_strdel(&tmp);
	return ((*str));
}
