/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection_pipe_aggregator.c                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/31 16:03:54 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void			redirect_aggregator_minus(t_fd *fd)
{
	if (fd->is_builtin != 1)
		close(fd->old_fd);
	else if (fd->is_builtin == 1 && fd->old_fd == 1)
		fd->new_fd = -1;
	else if (fd->is_builtin == 1 && fd->old_fd == 2)
		fd->new_fd = -1;
}

void			redirect_aggregator_right(t_fd *fd, t_redirect *red,
				t_process *p)
{
	fd->token = ft_strdup(">&");
	if (red->fd_in)
		fd->old_fd = ft_atoi(red->fd_in);
	else
		fd->old_fd = 1;
	if (ft_strcmp(red->fd_out, "-") == 0)
	{
		redirect_aggregator_minus(fd);
		return ;
	}
	if (is_all_num(red->fd_out) != 1)
	{
		fd->new_fd = redirection_find_file_fd(red->fd_out, red, p, fd);
		if (fd->new_fd == -1)
			return ;
	}
	else
	{
		fd->new_fd = ft_atoi(red->fd_out);
		if (isatty(fd->new_fd) == 0)
		{
			ft_printf_err_fd("42sh: %d: Bad file descriptor\n", fd->new_fd);
			p->exec_builtin = 0;
		}
	}
}

void			redirect_aggregator_left(t_fd *fd, t_redirect *red,
				t_process *p)
{
	fd->token = ft_strdup("<&");
	if (red->fd_in == NULL)
		fd->old_fd = 0;
	else
		fd->old_fd = ft_atoi(red->fd_in);
	fd->new_fd = ft_atoi(red->fd_out);
	if (is_all_num(red->fd_out) != 1)
	{
		ft_printf_err_fd("42sh: %s: ambiguous redirect\n", red->fd_out);
		p->exec_builtin = 0;
		fd->error = 1;
		return ;
	}
	if (isatty(fd->new_fd) == 0 ||
					(isatty(fd->old_fd) == 0 && fd->old_fd != 0))
	{
		ft_printf_err_fd("42sh: %s: Bad file descriptor\n", red->fd_out);
		p->exec_builtin = 0;
		fd->error = 1;
		return ;
	}
}

void			end_pipe_redirection(t_pos *pos, t_process *p, t_fd *fd,
				int is_builtin)
{
	(void)fd;
	if (pos->pipe > 0)
	{
		pos->act_fd_out = 1;
		if (is_builtin != 1)
		{
			close(pos->pipe);
			dup2(p->fd_in, 0);
		}
	}
}

void			init_pipe_redirection(t_pos *pos, t_process *p,
				int is_builtin, t_fd *fd)
{
	if (p->split == 'P')
	{
		if (is_builtin == 0)
			dup2(p->fd_out, 1);
		else if (is_builtin == 1 && p->redirect)
		{
			while (fd->next)
			{
				if (fd->old_fd == 1 && ft_strcmp(fd->token, "<<") != 0 &&
						ft_strcmp(fd->token, "<") != 0)
					pos->act_fd_out = fd->new_fd;
				else if (fd->old_fd == 2 && ft_strcmp(fd->token, "<<") != 0
						&& ft_strcmp(fd->token, "<") != 0)
					pos->act_fd_error = fd->new_fd;
				fd = fd->next;
			}
		}
		else
			pos->act_fd_out = p->fd_out;
	}
}
