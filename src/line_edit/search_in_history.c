/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   search_in_history.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/25 07:58:52 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/16 08:24:01 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		remove_last_link_hist(void)
{
	t_hist	*hist;

	hist = stock(NULL, 8);
	if (!hist)
		return ;
	while (hist && hist->next)
		hist = hist->next;
	ft_strdel(&hist->cmd);
}

t_hist		*search_up_complete_in_history(t_hist *hist, t_pos *pos)
{
	int		saved_cmd;

	saved_cmd = hist->cmd_no;
	while (hist->prev != NULL)
	{
		if (hist->prev)
			hist = hist->prev;
		if (ft_strncmp(hist->cmd, pos->saved_ans,
					ft_strlen(pos->saved_ans)) == 0)
			break ;
	}
	if (hist->cmd && hist->prev == NULL &&
		ft_strncmp(hist->cmd, pos->saved_ans, ft_strlen(pos->saved_ans)) != 0)
	{
		while (hist->cmd_no != saved_cmd && hist->next != NULL)
			hist = hist->next;
	}
	else if (hist->cmd)
	{
		free(pos->ans);
		pos->ans = ft_strdup(hist->cmd);
	}
	return (hist);
}

t_hist		*search_down_complete_in_history(t_hist *hist, t_pos *pos)
{
	int		saved_cmd;

	saved_cmd = hist->cmd_no;
	while (hist->next != NULL)
	{
		if (hist->next)
			hist = hist->next;
		if (hist->cmd != NULL && ft_strncmp(hist->cmd, pos->saved_ans,
					ft_strlen(pos->saved_ans)) == 0)
			break ;
	}
	if (hist->cmd != NULL && hist->next == NULL &&
		ft_strncmp(hist->cmd, pos->saved_ans, ft_strlen(pos->saved_ans)) != 0)
	{
		while (hist->cmd_no != saved_cmd && hist->prev != NULL)
			hist = hist->prev;
	}
	else if (hist->cmd)
	{
		free(pos->ans);
		pos->ans = ft_strdup(hist->cmd);
	}
	return (hist);
}
