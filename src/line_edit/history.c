/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 21:32:49 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 19:37:33 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		free_t_hist(t_hist *hist)
{
	t_hist	*tmp;

	while (hist->next)
		hist = hist->next;
	while (hist)
	{
		tmp = hist;
		if (hist->cmd)
			ft_strdel(&hist->cmd);
		hist = hist->prev;
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
	if (!(new = (t_hist*)malloc(sizeof(t_hist))))
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

t_hist		*create_history(t_pos *pos, t_hist *hist)
{
	char	*pwd;
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	pwd = getcwd(NULL, 255);
	pwd = ft_strjoinf(pwd, "/.history", 1);
	pos->history = open(pwd, O_RDWR | O_APPEND | O_CREAT, 0666);
	free(pwd);
	while ((ret = get_next_line(pos->history, &line)))
	{
		if (ft_strlen(line) > 0)
		{
			hist->cmd = ft_strnew(0);
			hist->cmd = ft_strjoinf(hist->cmd, line, 3);
			hist = add_list_back_hist(hist);
		}
		line = NULL;
	}
	return (hist);
}
