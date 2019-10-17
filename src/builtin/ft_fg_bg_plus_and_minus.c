/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fg_bg_plus_and_minus.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 16:50:53 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 18:02:14 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

t_job_list		*move_plus_and_minus_indicators_moves(t_job_list *save)
{
	save->j->current = ' ';
	while (save->next)
		save = save->next;
	save->j->current = '-';
	save->j->was_a_plus = 1;
	if (save->next)
	{
		save->next->j->current = '+';
		save->next->j->was_a_plus = 0;
	}
	else
	{
		save->j->current = '+';
		save->j->was_a_plus = 0;
	}
	return (save);
}

void			move_plus_and_minus_indicators(t_job_list *j, t_job_list *save)
{
	t_job_list *tmp;

	tmp = save;
	if (j && j->j && j->j->current == '+' && save == j)
		save = move_plus_and_minus_indicators_moves(save);
	else if (j && save && save->j && save->j->current == '+' && j != save)
	{
		save->j->was_a_plus = 0;
		return ;
	}
	else if (j && j->j && save && save->j)
	{
		if (j->j->current == '+')
			go_through_jobs_for_current(j, save);
	}
	save = tmp;
}

void			place_plus_and_minus_init_check(t_job_list *head, int *check)
{
	while (head)
	{
		if (head->j->current == '+')
		{
			head->j->current = '-';
			*check += 1;
		}
		else if (head->j->current == '-')
			head->j->current = ' ';
		head = head->next;
	}
}

void			place_plus_and_minus_check_null(t_job_list *head,
				t_job_list *tmp)
{
	while (head)
	{
		if (head->next && head->next->next == NULL)
		{
			head->next->j->current = '+';
			head->j->current = '-';
		}
		else if (head->next == NULL && head == tmp)
			head->j->current = '+';
		head = head->next;
	}
}

void			place_plus_and_minus(t_job_list *head, char split)
{
	int			check;
	t_job_list	*tmp;

	check = 0;
	tmp = head;
	place_plus_and_minus_init_check(head, &check);
	if (check == 0)
		place_plus_and_minus_check_null(head, tmp);
	while (head && split == '&')
	{
		head->j->was_a_plus = 0;
		head = head->next;
	}
	head = tmp;
	while (head && split == '&')
	{
		if (head->j->current == '-')
			head->j->was_a_plus = 1;
		head = head->next;
	}
}
