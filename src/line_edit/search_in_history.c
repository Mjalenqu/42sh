/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   search_in_history.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/25 07:58:52 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 13:52:53 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

t_hist		*search_up_complete_in_history(t_hist *hist, t_pos *pos)
{
	int		saved_cmd;

	saved_cmd = hist->cmd_no;
	while (1)
	{
		if (hist->prev)
			hist = hist->prev;
		if (ft_strncmp(hist->cmd, pos->saved_ans,
					ft_strlen(pos->saved_ans)) == 0)
			break ;
		if (hist->prev == NULL)
			break ;
	}
	if (hist->cmd && hist->prev == NULL &&
		ft_strncmp(hist->cmd, pos->saved_ans, ft_strlen(pos->saved_ans)) != 0)
	{
		while (hist->cmd_no != saved_cmd)
		{
			if (hist->next == NULL)
				break ;
			hist = hist->next;
		}
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
	while (1)
	{
		if (hist->next)
			hist = hist->next;
		if (hist->cmd != NULL && ft_strncmp(hist->cmd, pos->saved_ans,
					ft_strlen(pos->saved_ans)) == 0)
			break ;
		if (hist->next == NULL)
			break ;
	}
	if (hist->cmd != NULL && hist->next == NULL &&
		ft_strncmp(hist->cmd, pos->saved_ans, ft_strlen(pos->saved_ans)) != 0)
	{
		while (hist->cmd_no != saved_cmd)
		{
			if (hist->prev == NULL)
				break ;
			hist = hist->prev;
		}
	}
	else if (hist->cmd)
	{
		free(pos->ans);
		pos->ans = ft_strdup(hist->cmd);
	}
	return (hist);
}
