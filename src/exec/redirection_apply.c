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

char			*del_back_slash_and_quote_red(char *ar)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	if (ar)
	{
		res = browse_back_slash_and_quote(ar, 0, 0, NULL);
		free(ar);
	}
	return (res);
}

int				redirection_find_file_fd(char *file, t_redirect *red,
		t_process *p, t_fd *fd)
{
	char		*path;
	int			new_fd;

	if (file[0] != '/')
		path = ft_strdup("./");
	else
		path = ft_strnew(0);
	path = ft_strjoinf(path, file, 1);
	new_fd = redirection_get_argument_file_fd(red, path, p, 1);
	ft_strdel(&path);
	if (new_fd == -1)
		fd->error = 1;
	return (new_fd);
}

int				redirection_get_argument_file_fd(t_redirect *red, char *file,
		t_process *p, int new_fd_out)
{
	if (check_folders_rights(p, file, 1, NULL) == -1)
		return (-1);
	if (access(file, F_OK) != -1 && access(file, W_OK) != -1)
	{
		if (ft_strcmp(red->token, ">") == 0 || ft_strcmp(red->token, ">&") == 0)
			new_fd_out = open(file, O_RDWR | O_TRUNC);
		else if (ft_strcmp(red->token, "<") == 0)
			new_fd_out = open(file, O_RDWR | O_CREAT, 0666);
		else if (ft_strcmp(red->token, ">>") == 0)
			new_fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	else if (access(file, F_OK) != -1 && access(file, W_OK) == -1)
		ft_printf_err_fd("42sh: %s: permission denied\n", red->fd_out);
	else if (ft_strcmp(red->token, ">") == 0 || ft_strcmp(red->token, ">>") == 0
			|| ft_strcmp(red->token, ">&") == 0)
		new_fd_out = open(file, O_RDWR | O_CREAT, 0666);
	else
	{
		ft_printf_err_fd("42sh: %s: No such file or directory\n", red->fd_out);
		p->exec_builtin = 0;
		return (-1);
	}
	return (new_fd_out);
}

void			dup_fd_for_binaries(t_fd *fd)
{
	if (ft_strcmp(fd->token, "<") == 0 &&
			(fd->old_fd == -1 || fd->old_fd == 0))
		dup2(fd->new_fd, 0);
	else if (ft_strcmp(fd->token, "<") == 0)
		dup2(fd->new_fd, fd->old_fd);
	else if (ft_strcmp(fd->token, ">") == 0 ||
			ft_strcmp(fd->token, ">&") == 0 || ft_strcmp(fd->token, "<&") == 0)
		dup2(fd->new_fd, fd->old_fd);
	else if (ft_strcmp(fd->token, "<<") == 0)
	{
		dup2(fd->new_fd, 0);
		close(fd->new_fd);
	}
}

void			final_change_fd_for_redirections(t_fd *fd, t_pos *pos)
{
	while (fd)
	{
		if (fd->is_builtin == 0 && fd->error == 0)
			dup_fd_for_binaries(fd);
		else if (fd->is_builtin == 1)
		{
			if (fd->old_fd == 1)
				pos->act_fd_out = fd->new_fd;
			if (fd->old_fd == 2)
				pos->act_fd_error = fd->new_fd;
		}
		fd = fd->next;
	}
}
