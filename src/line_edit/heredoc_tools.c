/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heredoc_tools.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/01 18:58:58 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 14:07:43 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

void			init_t_heredoc(t_heredoc *hdoc)
{
	hdoc->to_find = NULL;
	hdoc->current_index = 0;
	hdoc->content = ft_strnew(0);
	hdoc->next = NULL;
	hdoc->prev = NULL;
}

t_heredoc		*add_list_back_heredoc(t_heredoc *heredoc)
{
	t_heredoc	*new;

	new = NULL;
	if (!(new = (t_heredoc*)malloc(sizeof(t_heredoc))))
		return (NULL);
	if (heredoc == NULL)
	{
		init_t_heredoc(new);
		return (new);
	}
	while (heredoc->next != NULL)
		heredoc = heredoc->next;
	init_t_heredoc(new);
	heredoc->next = new;
	new->prev = heredoc;
	return (new);
}

void			free_hdoc(t_heredoc *hdoc)
{
	t_heredoc				*tmp;

	if (hdoc == NULL)
		return ;
	while (hdoc->prev)
		hdoc = hdoc->prev;
	while (hdoc)
	{
		tmp = hdoc;
		hdoc = hdoc->next;
		ft_strdel(&tmp->content);
		ft_strdel(&tmp->to_find);
		free(tmp);
	}
	free(hdoc);
}

int				going_to_heredoc_end(t_pos *pos, int i)
{
	while (pos->ans[i])
	{
		if (i > 0 && pos->ans[i - 1] != 92)
		{
			if (pos->ans[i] == 32 || pos->ans[i] == '<' || pos->ans[i] == '>' ||
				pos->ans[i] == '&' || pos->ans[i] == '|' || pos->ans[i] == '\n'
				|| (pos->ans[i] == '$' && pos->ans[i + 1] == '{') ||
				pos->ans[i] == '"' || pos->ans[i] == 39)
				break ;
		}
		i++;
	}
	return (i);
}

char			*remove_backslash(char *ans)
{
	int			i;
	int			j;
	char		*new;

	i = ft_strlen(ans);
	new = ft_strnew(i);
	ft_bzero(new, i);
	i = 0;
	j = 0;
	while (ans[i])
	{
		if (ans[i] != 92)
			new[j++] = ans[i];
		i++;
	}
	ft_strdel(&ans);
	return (new);
}
