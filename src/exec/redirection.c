/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/19 13:34:01 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 13:35:30 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

static void	redirection_fd(int new, int old)
{
	dup2(new, old);
	close(new);
}

static int	redirection_file(t_redirect *redirect)
{
	if (ft_strcmp(redirect->token, ">") == 0)
	{
		if (!fd_right(redirect->fd_out))
			return (0);
		redirection_fd(redirect->open_out, redirect->fd);
	}
	if (ft_strcmp(redirect->token, ">>") == 0)
	{
		if (!fd_right(redirect->fd_out))
			return (0);
		redirection_fd(redirect->open_out, redirect->fd);
	}
	if (ft_strcmp(redirect->token, "<") == 0)
	{
		if (!fd_right(redirect->fd_out) || !ft_file_exists(redirect->fd_out))
			return (0);
		redirection_fd(redirect->open_in, STDIN_FILENO);
	}
	if (ft_strcmp(redirect->token, "<<") == 0)
	{
		redirection_fd(redirect->open_in, STDIN_FILENO);
	}
	return (1);
}

int			launch_redirection(t_process *p)
{
	t_redirect	*redirect;
	int			fd_in;
	int			fd_out;

	redirect = p->redirect;
	fd_in = 1;
	while (redirect)
	{
		if (ft_strcmp(redirect->token, "<<") == 0)
			fd_in = 1;
		else
			fd_in = ft_atoi(redirect->fd_in);
		if (!redirect->fd_in)
			fd_in = 1;
		fd_out = ft_atoi(redirect->fd_out);
		if (redirection_file(redirect) == 0)
			return (0);
		if (duplication(redirect, fd_in, fd_out) == 0)
			return (0);
		redirect = redirect->next;
	}
	return (1);
}
