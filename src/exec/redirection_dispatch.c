/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_new_redirection.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 19:07:24 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/01 11:34:57 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

int				is_all_num(char *str)
{
	int			i;

	i = 0;
	if (str[0] && str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		else
			i++;
	}
	return (1);
}

void			dispatch_redirection_with_token(t_fd *fd, t_redirect *red,
				t_process *p)
{
	if (ft_strcmp(red->token, "<") == 0)
		redirect_simple_left(fd, red, p);
	else if (ft_strcmp(red->token, ">") == 0 ||
			ft_strcmp(red->token, ">>") == 0)
		redirect_simple_right(fd, red, p);
	else if (ft_strcmp(red->token, ">&") == 0)
		redirect_aggregator_right(fd, red, p);
	else if (ft_strcmp(red->token, "<&") == 0)
		redirect_aggregator_left(fd, red, p);
	else if (ft_strcmp(red->token, "<<") == 0)
		redirect_heredoc(fd, red);
}

void			redirect_heredoc(t_fd *fd, t_redirect *red)
{
	fd->token = ft_strdup("<<");
	fd->new_fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	write(fd->new_fd, red->heredoc_content, ft_strlen(red->heredoc_content));
	write(fd->new_fd, "\n", 1);
	fd->new_fd = open("/tmp/heredoc", O_CREAT | O_RDWR, 0644);
}

void			free_fd_list(t_fd *fd)
{
	t_fd		*tmp;

	while (fd)
	{
		tmp = fd;
		fd = fd->next;
		ft_strdel(&tmp->token);
		free(tmp);
	}
}

void			get_all_redirections_done(t_process *p, t_pos *pos,
				t_redirect *red, int is_builtin)
{
	t_fd		*fd;
	t_fd		*head;

	fd = NULL;
	head = NULL;
	end_pipe_redirection(pos, p, fd, is_builtin);
	while (red)
	{
		red->fd_in = del_back_slash_and_quote_red(red->fd_in);
		red->fd_out = del_back_slash_and_quote_red(red->fd_out);
		fd = add_list_back_fd(fd);
		if (head == NULL)
			head = fd;
		while (fd->next)
			fd = fd->next;
		fd->is_builtin = is_builtin;
		dispatch_redirection_with_token(fd, red, p);
		red = red->next;
	}
	init_pipe_redirection(pos, p, is_builtin, head);
	final_change_fd_for_redirections(head, pos);
	free_fd_list(head);
}
