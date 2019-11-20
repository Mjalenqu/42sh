/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd_verif.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/26 19:11:29 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 18:34:27 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

char		*print_pwd(t_var *var)
{
	char	*pwd;

	pwd = ft_get_val("PWD", var, ENVIRONEMENT);
	if (pwd != NULL && verif_path(pwd, 0, 0) != 0)
		return (ft_strdup(pwd));
	else
		return (getcwd(NULL, 1000));
}

char		*verif_p_option_path(char *new_path, int i, int absolute)
{
	char	**split_path;
	char	*test;

	if (new_path && new_path[0] == '/')
		absolute = 1;
	test = ft_strnew(0);
	split_path = ft_strsplit(new_path, '/');
	while (split_path[i])
	{
		if (absolute == 1 && i == 0)
			test = ft_strjoinf(test, "/", 1);
		test = ft_strjoinf(test, split_path[i], 1);
		test = ft_strjoinf(test, "/", 1);
		if (verif_path(test, 1, 0) == 0)
		{
			ft_strdel(&new_path);
			ft_free_tab(split_path);
			free(test);
			return (NULL);
		}
		i++;
	}
	ft_free_tab(split_path);
	free(test);
	return (new_path);
}

int			check_access_path(char *path, int usage, int i, int mute)
{
	if (access(path, F_OK) == -1)
	{
		if (usage == 0)
			return (0);
		print_cd_error(path, i, mute, 1);
	}
	else if (access(path, X_OK) == -1)
	{
		if (usage == 0)
			return (0);
		print_cd_error(path, i, mute, 2);
	}
	else
		return (1);
	return (0);
}

int			verif_path(char *path, int mute, int usage)
{
	DIR			*file;
	int			i;
	struct stat	s_type;

	if (path != NULL)
		lstat(path, &s_type);
	file = NULL;
	i = ft_strlen(path) - 2;
	while (i > 0 && path[i] != '/')
		i--;
	if (usage == 1 && (path == NULL || (s_type.st_mode & S_IFMT) != S_IFDIR))
	{
		if (path == NULL || (((s_type.st_mode & S_IFMT) != S_IFDIR) &&
					access(path, F_OK) != -1))
		{
			print_cd_error(path, i, mute, 0);
			return (0);
		}
		if (check_access_path(path, usage, i, mute) == 0)
			return (0);
	}
	else
		return (check_access_path(path, usage, i, mute));
	return (1);
}

int			check_arguments_number(t_process *p, int *i, int *option,
			t_var *old_env)
{
	if ((*option = get_cd_option(p->cmd, i, 0, 0)) == -1)
	{
		free_env_list(old_env);
		ft_printf_err_fd("cd: usage: cd [-L|-P] [dir]\n");
		return (1);
	}
	if (p->cmd[*i] && p->cmd[*i + 1])
	{
		free_env_list(old_env);
		ft_printf_err_fd("cd: too many arguments\n");
		return (1);
	}
	return (0);
}
