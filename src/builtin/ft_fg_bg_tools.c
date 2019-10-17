/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fg_bg_tools.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 16:07:08 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 12:20:58 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

t_job_list		*find_plus_jb(t_job_list *j)
{
	t_job_list	*tmp;

	tmp = j;
	while (tmp)
	{
		if (tmp->j->current == '+')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_job			*find_plus(t_job_list *j)
{
	t_job_list	*tmp;

	tmp = j;
	while (tmp)
	{
		if (tmp->j->current == '+')
			return (tmp->j);
		tmp = tmp->next;
	}
	return (NULL);
}

void			go_through_jobs_for_current(t_job_list *j, t_job_list *save)
{
	j->j->current = ' ';
	if (save->j->current == '-')
	{
		save->j->current = '+';
		save->j->was_a_plus = 0;
	}
	while (save->next)
	{
		if (save->next->j->current == '-')
		{
			save->next->j->current = '+';
			save->next->j->was_a_plus = 0;
			save->j->current = '-';
			save->j->was_a_plus = 1;
		}
		save = save->next;
	}
}

void			change_plus_and_minus_indicators(t_job_list *jb, t_job *j,
				t_job_list *save)
{
	if (jb->j == j)
		return ;
	while (save)
	{
		if (save->j->current == '-')
		{
			save->j->was_a_plus = 0;
			save->j->current = ' ';
		}
		save = save->next;
	}
	if (j)
	{
		j->was_a_plus = 1;
		j->current = '-';
	}
	jb->j->current = '+';
}

void			repare_plus_and_minus(t_job_list *save, int check_minus,
				int check_plus)
{
	t_job_list	*tmp;

	tmp = save;
	while (tmp)
	{
		if (tmp->j->current == '+')
			check_plus = 1;
		if (tmp->j->current == '-')
			check_minus = 1;
		tmp = tmp->next;
	}
	while (save)
	{
		if (save->j->was_a_plus == 1)
			save->j->was_a_plus = 0;
		if (save->next == NULL && check_plus == 0)
			save->j->current = '+';
		if (save->next && save->next->next == NULL && check_minus == 0)
		{
			save->j->current = '-';
			save->j->was_a_plus = 1;
		}
		save = save->next;
	}
}
