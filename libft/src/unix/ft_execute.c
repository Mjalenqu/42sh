/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_execute.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shthevak <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/15 15:32:21 by shthevak     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/15 15:43:17 by shthevak    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_unix.h"

int	ft_execute(char *exec, char **opt, char **env)
{
	int		w;
	pid_t	p;

	p = fork();
	if (p == 0)
	{
		if (execve(exec, opt, env) == -1)
			return (0);
	}
	else
		wait(&w);
	return (1);
}
