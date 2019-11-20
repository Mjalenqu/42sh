/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_file_arights.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/15 16:43:27 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_unix.h"

int	ft_file_arights(char *path)
{
	if (access(path, R_OK | W_OK | X_OK) != -1)
		return (1);
	return (0);
}
