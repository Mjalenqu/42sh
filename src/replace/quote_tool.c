/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   quote_tool.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 20:06:15 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 20:09:49 by mdelarbr    ###    #+. /#+    ###.fr     */
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
