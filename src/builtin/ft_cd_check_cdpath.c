/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd_check_cdpath.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 16:12:49 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 18:34:41 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void		restore_old_env(t_var *old_env, t_var **var, t_pos *pos)
{
	add_list_env(var, ENVIRONEMENT, ft_strdup("OLDPWD"),
			ft_strdup(ft_get_val("OLDPWD", old_env, ENVIRONEMENT)));
	add_list_env(var, ENVIRONEMENT, ft_strdup("HOME"),
			ft_strdup(ft_get_val("HOME", old_env, ENVIRONEMENT)));
	add_list_env(var, ENVIRONEMENT, ft_strdup("PWD"),
			ft_strdup(ft_get_val("PWD", old_env, ENVIRONEMENT)));
	ft_strdel(&pos->pwd);
	pos->pwd = ft_strdup(ft_get_val("PWD", *var, ENVIRONEMENT));
	if (!pos->pwd)
		pos->pwd = getcwd(NULL, 1000);
}

int			finish_ft_cd(char *new_path, t_pos *pos, t_var *old_env, int option)
{
	t_var		*var;
	t_process	*p;

	p = to_stock(NULL, 3);
	var = stock(NULL, 6);
	if (verif_path(new_path, 1, 1) == 0)
	{
		ft_strdel(&new_path);
		free_env_list(old_env);
		return (1);
	}
	else
		new_path = error_in_new_path(new_path);
	chdir(new_path);
	ft_strdel(&pos->pwd);
	if (option == 'P')
		pos->pwd = getcwd(NULL, 1000);
	else
		pos->pwd = ft_strdup(new_path);
	replace_pwd_vars_in_env(&var, new_path, option);
	free_env_list(old_env);
	return (0);
}

void		print_cd_error(char *path, int i, int mute, int usage)
{
	t_pos	*pos;

	pos = to_stock(NULL, 1);
	if (mute && pos->error_printed == 0)
	{
		if (i < 0)
			i = 0;
		if (usage == 0 && path && path + i)
			ft_printf_err_fd("42sh: cd: %s: is not a directory\n", path + i);
		else if (usage == 0)
			ft_printf_err_fd("42sh: cd : not a directory\n");
		if (usage == 1 && path && path + i + 1 && path[i] == '/')
			ft_printf_err_fd("42sh: cd: %s: No such file or directory\n",
					path + i + 1);
		else if (usage == 1 && path && path + i)
			ft_printf_err_fd("42sh: cd: %s: No such file or directory\n",
					path + i);
		else if (usage == 1)
			ft_printf_err_fd("42sh: cd: No such file or directory\n");
		if (usage == 2 && path && path + i)
			ft_printf_err_fd("42sh: cd: %s: permission denied\n", path + i);
		else if (usage == 2)
			ft_printf_err_fd("42sh: cd: permission denied\n");
	}
}

char		*get_new_path_content(char *new_path, char *cdpath, char *cmd)
{
	new_path = ft_strjoinf(new_path, cdpath, 1);
	if (new_path[ft_strlen(new_path) - 1] != '/')
		new_path = ft_strjoinf(new_path, "/", 1);
	new_path = ft_strjoinf(new_path, cmd, 1);
	return (new_path);
}

char		*verif_path_in_cdpath(char *path, t_var *var, char **cmd, int j)
{
	char	**cdpaths;
	int		i;
	char	*new_path;

	while (cmd[j] && cmd[j][0] == '-')
		j++;
	if (!cmd[j])
		return (cmd[j - 1]);
	i = 0;
	cdpaths = ft_strsplit(ft_get_val("CDPATH", var, ENVIRONEMENT), ':');
	while (cdpaths[i])
	{
		new_path = ft_strnew(0);
		new_path = get_new_path_content(new_path, cdpaths[i], cmd[j]);
		if (verif_path(new_path, -1, 0) != 0)
		{
			path = new_path;
			ft_free_tab(cdpaths);
			return (new_path);
		}
		i++;
		ft_strdel(&new_path);
	}
	ft_free_tab(cdpaths);
	return (ft_strdup(cmd[j]));
}
