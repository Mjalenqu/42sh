/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection_apply.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/31 16:10:01 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 18:35:33 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

int				check_splited_folds(char *act_fold, char **path, int i,
				t_process *p)
{
	struct stat	s_type;

	while (path[i])
	{
		act_fold = ft_strjoinf(act_fold, "/", 1);
		act_fold = ft_strjoinf(act_fold, path[i], 1);
		lstat(act_fold, &s_type);
		if (access(act_fold, F_OK) != -1 && (s_type.st_mode & S_IFMT) ==
				S_IFDIR && access(act_fold, X_OK) == -1)
		{
			ft_printf_err_fd("42sh: %s: permission denied\n", path[i]);
			p->exec_builtin = 0;
			ft_free_tab(path);
			ft_strdel(&act_fold);
			return (-1);
		}
		i++;
	}
	ft_free_tab(path);
	ft_strdel(&act_fold);
	return (0);
}

int				check_folders_rights(t_process *p, char *file, int i,
		char *act_fold)
{
	char		**path;
	struct stat	s_type;

	lstat(file, &s_type);
	if ((s_type.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_printf_err_fd("42sh: %s: Is a directory\n", file);
		p->exec_builtin = 0;
		return (-1);
	}
	path = ft_strsplit(file, '/');
	if (file[0] == '/')
	{
		act_fold = ft_strdup("/");
		act_fold = ft_strjoinf(act_fold, path[0], 1);
	}
	else
		act_fold = ft_strdup(path[0]);
	return (check_splited_folds(act_fold, path, i, p));
}
