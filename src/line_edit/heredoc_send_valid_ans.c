/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heredoc_send_valid_ans.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/01 18:56:46 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/31 11:01:16 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int				check_if_to_find_is_not_empty(t_heredoc *hdoc)
{
	while (hdoc)
	{
		if (!hdoc->to_find || check_ans(hdoc->to_find) == 1)
			return (-1);
		hdoc = hdoc->next;
	}
	return (0);
}

char			*put_symbol_in_ans(char *ans, int i)
{
	while (ans[i])
	{
		if (ans[i] == ' ')
			ans[i] = -1;
		i++;
	}
	return (ans);
}

void			heredoc_ctrl_d(t_pos *pos, t_hist **hist)
{
	t_heredoc	*hdoc;

	while (pos->hdoc->prev)
		pos->hdoc = pos->hdoc->prev;
	hdoc = pos->hdoc;
	while (hdoc && hdoc->current_index == 1)
		hdoc = hdoc->next;
	hdoc->content = ft_strjoinf(hdoc->content, hdoc->to_find, 1);
	hdoc->content = ft_strjoinf(hdoc->content, " ", 1);
	hdoc->current_index = 1;
	if (hdoc->next == NULL)
	{
		*hist = entry_is_complete(pos, *hist);
		pos->active_heredoc = 0;
	}
}

int				fill_ans_heredoc(t_pos *pos, int i, int j)
{
	j = i;
	while (pos->ans[i])
	{
		if (pos->ans[i] == '<' && pos->ans[i + 1] == '<' &&
			(i == 0 || is_my_index_open(pos, 0, -1, i)) && add_space(pos, &i))
			break ;
		i += 1;
	}
	if (pos->ans[i])
		i += 2;
	while (pos->ans[i] && (pos->ans[i] == 32 || (pos->ans[i] >= 9 &&
					pos->ans[i] <= 13)))
		i += 1;
	if (pos->hdoc)
		i += ft_strlen(pos->hdoc->to_find);
	pos->ans_heredoc = ft_strjoinf(pos->ans_heredoc,
			ft_strsub(pos->ans, j, i - j), 3);
	if (pos->hdoc == NULL)
		return (ft_strlen(pos->ans));
	pos->ans_heredoc = ft_strjoinf(pos->ans_heredoc, " ", 1);
	pos->ans_heredoc = ft_strjoinf(pos->ans_heredoc, pos->hdoc->content, 1);
	pos->hdoc = pos->hdoc->next;
	if (i > ft_strlen(pos->ans))
		return (ft_strlen(pos->ans));
	return (i);
}

void			remake_pos_ans(t_pos *pos)
{
	int			i;
	t_heredoc	*tmp;

	i = 0;
	while (pos->hdoc && pos->hdoc->prev)
		pos->hdoc = pos->hdoc->prev;
	tmp = pos->hdoc;
	free(pos->ans);
	pos->ans = ft_strdup(pos->ans_heredoc);
	pos->ans_heredoc = ft_secure_free(pos->ans_heredoc);
	pos->ans_heredoc = ft_strnew(0);
	while (pos->ans[i])
		i = fill_ans_heredoc(pos, i, 0);
	pos->hdoc = tmp;
	free(pos->ans);
	pos->ans = ft_strdup(pos->ans_heredoc);
	pos->ans_heredoc = ft_secure_free(pos->ans_heredoc);
	pos->active_heredoc = 0;
	free_hdoc(pos->hdoc);
	pos->hdoc = NULL;
	pos->ans_heredoc_save = ft_secure_free(pos->ans_heredoc_save);
}
