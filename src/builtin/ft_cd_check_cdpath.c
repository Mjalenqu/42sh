/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd_check_cdpath.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 16:12:49 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 13:29:58 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int			finish_ft_cd(char *new_path, t_pos *pos, t_var **var, int option)
{
	if (verif_path(new_path, 1, 1) == 0)
	{
		ft_strdel(&new_path);
		return (1);
	}
	chdir(new_path);
	ft_strdel(&pos->pwd);
	if (option == 'P')
		pos->pwd = getcwd(NULL, 1000);
	else
		pos->pwd = ft_strdup(new_path);
	replace_pwd_vars_in_env(var, new_path, option);
	return (0);
}

void		print_cd_error(char *path, int i, int mute, int usage)
{
	if (mute)
	{
		if (usage == 0)
			ft_printf_err("42sh: cd: %s: is not a directory\n", path + i);
		if (usage == 1)
			ft_printf_err("42sh: cd: %s: No such file or directory\n",
					path + i + 1);
		if (usage == 2)
			ft_printf_err("42sh: cd: %s: permission denied\n", path + i);
	}
}

char		*get_new_path_content(char *new_path, char *cdpath, char *cmd)
{
	new_path = ft_strjoinf(new_path, cdpath, 1);
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
