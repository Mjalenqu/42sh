/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   h.c                                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/04 10:59:46 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 11:03:28 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/hache.h"

int		hache_function(char *str)
{
	int		size;
	int		nb;
	int     i;

	i = 0;
	nb = 0;
	size = ft_strlen(str);
	while (str[i])
		nb += str[i++];
	nb %= 100;
	
	return (nb);
}

int		main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	printf("res: %s\n", av[1]);
	printf("int -> __%d__\n", hache_function(av[1]));
	return (0);
}