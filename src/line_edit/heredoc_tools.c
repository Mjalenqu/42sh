/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heredoc_tools.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/01 18:58:58 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 16:12:48 by rlegendr    ###    #+. /#+    ###.fr     */
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
	if (!(new = (t_heredoc*)ft_malloc(sizeof(t_heredoc))))
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
	int		check;

	check = 0;
	while (pos->ans[i])
	{
		if (pos->ans[i - 1] == 92 && pos->ans[i] != 92 && odd_backslash(i - 1,
				pos->ans) == 0)
			check = 1;
		if ((i > 0 && pos->ans[i - 1] != 92) || check == 1)
		{
			if (pos->ans[i] == 32 || pos->ans[i] == '<' || pos->ans[i] == '>' ||
				pos->ans[i] == '&' || pos->ans[i] == '|' || pos->ans[i] == '\n'
				|| (pos->ans[i] == '$' && pos->ans[i + 1] == '{') ||
				pos->ans[i] == '"' || pos->ans[i] == 39 || pos->ans[i] == ';')
				break ;
		}
		check = 0;
		i++;
	}
	return (i);
}

char			*remove_backslash(char *ans, int i, int j)
{
	int			nb_backslash;
	char		*new;

	new = ft_strnew(ft_strlen(ans));
	ft_bzero(new, ft_strlen(ans));
	while (i <= ft_strlen(ans))
	{
		nb_backslash = 0;
		while (ans[i] == 92)
		{
			nb_backslash++;
			i++;
		}
		if (nb_backslash)
		{
			while (nb_backslash > 1)
			{
				new[j++] = 92;
				nb_backslash -= 2;
			}
		}
		else
			new[j++] = ans[i++];
	}
	return (new);
}
