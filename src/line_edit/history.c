/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 21:32:49 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 09:05:02 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		free_t_hist(t_hist *hist)
{
	t_hist	*tmp;

	while (hist->prev)
		hist = hist->prev;
	while (hist)
	{
		tmp = hist;
		ft_strdel(&tmp->cmd);
		hist = hist->next;
		free(tmp);
	}
}

void		init_t_hist(t_hist *hist)
{
	if (hist == NULL)
		return ;
	hist->cmd = NULL;
	hist->next = NULL;
	hist->prev = NULL;
	hist->cmd_no = 0;
}

t_hist		*add_list_back_hist(t_hist *hist)
{
	t_hist	*new;

	new = NULL;
	if (!(new = (t_hist*)ft_malloc(sizeof(t_hist))))
		return (NULL);
	if (hist == NULL)
	{
		init_t_hist(new);
		return (new);
	}
	while (hist->next != NULL)
		hist = hist->next;
	init_t_hist(new);
	hist->next = new;
	new->prev = hist;
	new->cmd_no = hist->cmd_no + 1;
	return (new);
}

int			open_hist(t_pos *pos)
{
	char *pwd;

	pwd = getcwd(NULL, 1000);
	pwd = ft_strjoinf(pwd, "/.history", 1);
	pos->history = open(pwd, O_RDWR | O_APPEND | O_CREAT, 0666);
	ft_strdel(&pwd);
	if (pos->history == -1)
		return (-1);
	return (0);
}

t_hist		*create_history(t_pos *pos, t_hist *hist)
{
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	if (open_hist(pos) == -1)
		return (hist);
	while ((ret = get_next_line(pos->history, &line)))
	{
		if (ft_strlen(line) > 0)
		{
			transform_tab_into_space(line);
			hist->cmd = ft_strdup(line);
			hist = add_list_back_hist(hist);
		}
		ft_strdel(&line);
	}
	stock(hist, 7);
	return (hist);
}
