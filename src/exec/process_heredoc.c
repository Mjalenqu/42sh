/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_heredoc.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 12:48:03 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/31 10:28:05 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

int			go_next_token(t_lexeur **res, int *t)
{
	int		i;

	i = 0;
	if (res[*t] && res[*t + 1] && res[*t + 1]->token == (enum e_token)-1)
		(*t)++;
	while (res[*t] && res[*t]->word)
	{
		i++;
		(*t)++;
	}
	return (i);
}

void		fill_heredoc_init(t_lexeur **res, t_redirect *tmp, int *t)
{
	tmp->token = g_fill_token[res[*t]->token].name;
	tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 1;
	tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 1;
}

void		init_fd_in_and_out(t_lexeur **res, int *t, t_redirect *tmp)
{
	if (res[*t]->token != 8 && res[*t]->token != 5)
		tmp->fd_in = (res[*t]->fd_in) ? ft_strdup(res[*t]->fd_in) : NULL;
	else if (res[*t]->fd_in)
		tmp->fd_in = ft_strdup(res[*t]->fd_in);
	else
		tmp->fd_in = NULL;
	tmp->fd_out = (res[*t]->fd_out) ? ft_strdup(res[*t]->fd_out) : NULL;
}
