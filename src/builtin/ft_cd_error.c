/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/26 12:58:07 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 17:02:34 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int			only_dot(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '.' && str[i] != '/')
			return (0);
		i++;
	}
	return (1);
}

char		*error_in_new_path(char *new_path)
{
	int		i;
	int		error;

	error = 0;
	if (only_dot(new_path) == 1)
		return (new_path);
	if ((i = 0) == 0 && new_path[0] != '/')
	{
		ft_printf("new_path = [%s]\n", new_path);
		ft_printf_fd("42sh: cd: error: file name too long\n");
		error = 1;
	}
	while (new_path && new_path[i] && error == 0)
	{
		if (ft_strncmp(new_path + i, "./", 2) == 0 ||
			ft_strncmp(new_path + i, "../", 3) == 0)
			error = 1;
		i++;
	}
	if (error == 1)
	{
		free(new_path);
		new_path = getcwd(NULL, 1000);
	}
	return (new_path);
}
