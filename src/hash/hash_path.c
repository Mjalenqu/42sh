/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_path.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 09:43:55 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 15:53:10 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/hash.h"

int					test_all_paths_existence(char **paths, char *arg, int *i)
{
	int				denied;

	denied = 0;
	while (paths != NULL && paths[*i])
	{
		paths[*i] = ft_strjoinf(paths[*i], "/", 1);
		paths[*i] = ft_strjoinf(paths[*i], arg, 1);
		if (access(paths[*i], F_OK) == 0 && access(paths[*i], X_OK) == 0)
			return (1);
		else if (access(paths[*i], F_OK) == 0 && access(paths[*i], X_OK) != 0)
			denied -= 1;
		*i += 1;
	}
	return (denied);
}

char				*absolute_path(char *path, char *tmp)
{
	DIR		*file;

	if (path[0] == '.')
	{
		ft_strdel(&path);
		path = ft_strjoinf(getcwd(NULL, 1000), tmp + 1, 1);
	}
	if ((file = opendir(path)) != NULL)
	{
		ft_printf_err("42sh: %s: is a directory\n", tmp);
		closedir(file);
	}
	if (access(path, F_OK) == -1)
		ft_printf_err("42sh: %s: No such file or directory\n", tmp);
	else if (access(path, X_OK) == -1)
		ft_printf_err("42sh: %s: permission denied\n", tmp);
	else
	{
		ft_strdel(&tmp);
		return (path);
	}
	ft_strdel(&tmp);
	ft_strdel(&path);
	return (NULL);
}

char				*path_found(char **paths, int i, char *ans, char *arg)
{
	ans = fill_hash_table(paths[i], arg);
	ft_free_tab(paths);
	ft_strdel(&arg);
	return (ans);
}

char				*path_denied(char **paths, char *arg, int denied)
{
	if (denied != 0)
		ft_printf_err("42sh: %s: permission denied\n", arg);
	else
		ft_printf_err("42sh: %s: command not found\n", arg);
	ft_free_tab(paths);
	ft_strdel(&arg);
	return (NULL);
}

int					scan_name_for_undesired_symbols(char *str)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (((ft_isalpha(str[i]) == 0) || (str[i] < '0' && str[i] > '9')) &&
				(str[i] != 45 && str[i] != 95))
			return (-1);
		i++;
	}
	return (0);
}
