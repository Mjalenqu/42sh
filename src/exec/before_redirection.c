/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   before_redirection.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/19 13:34:01 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 08:24:55 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

int			fd_right(char *path)
{
	if (access(path, F_OK) != -1)
	{
		if (opendir(path) != NULL)
			ft_printf_err("42sh: %s: Is a directory\n", path);
		else if (access(path, R_OK) == -1)
			ft_printf_err("42sh: %s: Permission denied\n", path);
		else
			return (1);
	}
	else
		return (1);
	return (0);
}

void		before_redirection_file_in(t_redirect *redirect)
{
	if (ft_strcmp(redirect->token, "<") == 0)
	{
		if ((redirect->open_in = open(redirect->fd_out, O_RDONLY)) == -1)
			ft_printf_err("42sh: %s: No such file or directory\n",
			redirect->fd_out);
	}
	if (ft_strcmp(redirect->token, "<<") == 0)
	{
		redirect->open_in = open(PATH_HEREDOC, O_CREAT | O_RDWR | O_TRUNC,
			S_IRUSR | S_IWUSR);
		write(redirect->open_in, redirect->heredoc_content,
			ft_strlen(redirect->heredoc_content));
		write(redirect->open_in, "\n", 1);
		redirect->open_in = open(PATH_HEREDOC, O_CREAT |
		O_RDWR, S_IRUSR | S_IWUSR);
	}
}

void		before_redirection_file(t_redirect *redirect)
{
	if (ft_strcmp(redirect->token, ">") == 0)
	{
		redirect->open_out = open(redirect->fd_out,
			O_CREAT | O_RDWR | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	if (ft_strcmp(redirect->token, ">>") == 0)
	{
		if (fd_right(redirect->fd_out))
			redirect->open_out = open(redirect->fd_out,
				O_CREAT | O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	before_redirection_file_in(redirect);
}

void		before_redirection(t_process *p)
{
	t_redirect	*redirect;

	while (p)
	{
		p->fd_error = STDERR_FILENO;
		p->fd_in = 0;
		p->fd_out = 1;
		redirect = p->redirect;
		while (redirect)
		{
			before_redirection_file(redirect);
			redirect = redirect->next;
		}
		p = p->next;
	}
}
