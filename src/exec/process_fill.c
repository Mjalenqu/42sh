/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_fill.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 17:07:12 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 08:43:44 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/lexeur.h"

int			fill_heredoc(t_lexeur **res, t_redirect *tmp, int *t)
{
	int		j;
	int		size;
	int		diff;

	size = 0;
	j = (*t);
	tmp->token = g_fill_token[res[*t]->token].name;
	tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 1;
	tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 1;
	tmp->heredoc_content = get_content(res[*t]->redirection, res, t, &size);
	tmp->fd_out = NULL;
	tmp->fd_in = NULL;
	tmp->next = NULL;
	diff = (*t) - j;
	(*t) = j;
	diff--;
	if (tmp->heredoc_content != NULL)
		return (size + 1);
	return (diff);
}

int			fill_ag_first(t_redirect *tmp, t_lexeur **res, int *t)
{
	tmp->heredoc_content = NULL;
	if (res[*t]->token == 7)
		return (fill_heredoc(res, tmp, t));
	if (res[*t]->token != 4 && res[*t]->token != 6 && res[*t]->token != 9)
	{
		tmp->fd_in = (res[*t]->fd_in) ? ft_strdup(res[*t]->fd_in) : NULL;
		tmp->fd_out = (res[*t]->fd_out) ? ft_strdup(res[*t]->fd_out) : NULL;
	}
	else
	{
		tmp->fd_in = NULL;
		tmp->fd_out = (res[*t]->redirection) ? ft_strdup(res[*t]->redirection)
		: NULL;
	}
	if (res[*t]->token == 4 || res[*t]->token == 6 || res[*t]->token == 9)
		tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 1;
	else
		tmp->fd = (res[*t]->token == 8) ? 0 : 1;
	tmp->token = (res[*t]->token) ? ft_strdup(g_fill_token[res[*t]->token].name)
	: NULL;
	tmp->next = NULL;
	return (go_next_token(res, t));
}

int			fill_ag_next(t_redirect *tmp, t_lexeur **res, int *t)
{
	while (tmp->next)
		tmp = tmp->next;
	make_tmp_great_again(&tmp);
	if (res[*t]->token == 7)
		return (fill_heredoc(res, tmp, t));
	if (res[*t]->token != 4 && res[*t]->token != 6 && res[*t]->token != 9)
	{
		tmp->fd_in = (res[*t]->fd_in) ? ft_strdup(res[*t]->fd_in) : NULL;
		tmp->fd_out = (res[*t]->fd_out) ? ft_strdup(res[*t]->fd_out) : NULL;
	}
	else
	{
		tmp->fd_in = NULL;
		tmp->fd_out = (res[*t]->redirection) ? ft_strdup(res[*t]->redirection)
		: NULL;
	}
	if (res[*t]->token == 4 || res[*t]->token == 6 || res[*t]->token == 9)
		tmp->fd = (res[*t]->fd_in) ? ft_atoi(res[*t]->fd_in) : 1;
	else
		tmp->fd = 1;
	tmp->token = (res[*t]->token) ? ft_strdup(g_fill_token[res[*t]->token].name)
	: NULL;
	tmp->next = NULL;
	return (go_next_token(res, t));
}

void		go_next_heredoc(t_lexeur **res, int *i, int *done)
{
	char	*tag;

	(*done) = 1;
	tag = ft_strdup(res[*i]->redirection);
	(*i)++;
	while (res[*i])
	{
		if (!ft_strcmp(res[*i]->word, tag))
			break ;
		(*i)++;
	}
	if (res[*i])
		(*i)++;
	ft_strdel(&tag);
}

void		fill_all_cmd(t_lexeur **res, t_job **j, int *k, int i)
{
	int		done;

	while (res[i] && ((res[i]->word) || (res[i]->token != 0
	&& res[i]->token != 1 &&
	res[i]->token != 2 && res[i]->token != 3 && res[i]->token != 10)))
	{
		done = 0;
		if (res[i]->token == 7)
			go_next_heredoc(res, &i, &done);
		else if (res[i] && res[i]->word)
		{
			(*j)->p->cmd[*k] = ft_strdup(res[i]->word);
			(*k)++;
		}
		if (res[i] && !done)
			i++;
	}
}
