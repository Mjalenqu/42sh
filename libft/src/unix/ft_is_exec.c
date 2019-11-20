/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_is_exec.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/18 15:42:07 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_unix.h"

int		ft_is_exec(char *str)
{
	if (ft_file_exists(str))
	{
		if (ft_file_xrights(str))
			return (1);
	}
	return (0);
}
