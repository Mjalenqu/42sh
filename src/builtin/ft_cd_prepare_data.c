/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd_prepare_data.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/26 19:10:28 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 13:39:02 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

char	*move_to_home_dir(t_var **var)
{
	char	*path;

	if ((path = ft_get_val("HOME", *var, TEMP)) == NULL)
		path = ft_get_val("HOME", *var, ENVIRONEMENT);
	if (path == NULL)
	{
		ft_printf_err("42sh: cd: HOME not set\n");
		return (NULL);
	}
	else if (verif_path(path, 1, 0) == 0)
		return (NULL);
	return (ft_strdup(path));
}

char	*move_to_oldpwd(t_var **var)
{
	char	*path;

	path = ft_get_val("OLDPWD", *var, ENVIRONEMENT);
	if (path == NULL)
	{
		ft_printf_err("42sh: cd: OLDPWD not set\n");
		return (NULL);
	}
	else if (verif_path(path, 1, 0) == 0)
		return (NULL);
	return (ft_strdup(path));
}

char	*go_to_absolute_path(char *cmd, t_var **var)
{
	char	pwd[1000];
	char	*ret;

	ret = NULL;
	if ((ret = ft_get_val("PWD", *var, ENVIRONEMENT)) != NULL)
	{
		if (cmd[0] != '/')
			ret = ft_strjoin(ret, "/");
		return (ft_strjoinf(ret, cmd, 1));
	}
	getcwd(pwd, 1000);
	if (cmd[0] != '/')
		ret = ft_strjoin(pwd, "/");
	return (ft_strjoinf(ret, cmd, 1));
}

char	*replace_double_dot_by_real_path(char *path)
{
	int		i;

	if ((i = ft_strlen(path) - 2) == -1)
		return (path);
	while (i > 0 && path[i] != '/')
		i--;
	path[i + 1] = '\0';
	return (path);
}

char	*fill_new_path(char ***tmp, char *new_path, char *cmd, t_var **var)
{
	if (cmd[0] != '/')
		new_path = go_to_absolute_path(cmd, var);
	else
		new_path = ft_strdup(cmd);
	*tmp = ft_strsplit(new_path, '/');
	new_path = ft_secure_free(new_path);
	new_path = ft_strdup("/");
	return (new_path);
}
