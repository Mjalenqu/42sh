/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_create_file.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/15 14:57:40 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/17 16:12:56 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_unix.h"

int		ft_create_file(char *path)
{
	char *(tab[3]);

	if (access(path, F_OK) != 0)
	{
		if (access("/usr/bin/touch", X_OK) == 0)
		{
			tab[0] = "/usr/bin/touch";
			tab[1] = path;
			tab[2] = NULL;
			if (ft_execute("/usr/bin/touch", tab, NULL))
				return (1);
			return (0);
		}
		return (0);
	}
	return (0);
}
