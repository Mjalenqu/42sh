/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_function.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:43:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 18:42:43 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

void		remove_job_free(t_job_list **job_list, t_job_list **last,
			t_job_list **start)
{
	t_job_list *next;

	next = (*job_list)->next;
	if (*last == NULL)
		*start = next;
	else
		(*last)->next = next;
	free_job((*job_list)->j);
	free(*job_list);
	*job_list = next;
}

void		return_to_the_copy(t_job_list *start, t_save_job *copy)
{
	while (copy)
	{
		start->j->current = copy->current;
		start->j->was_a_plus = copy->was_a_plus;
		copy = copy->next;
		start = start->next;
	}
}

void		remove_job(int id, int i)
{
	t_job_list	*job_list;
	t_job_list	*start;
	t_job_list	*last;
	t_save_job	*copy;

	copy = stock_t_job(NULL, 3);
	start = stock(NULL, 10);
	job_list = start;
	last = NULL;
	while (job_list)
	{
		if (job_list->j->id == id)
			remove_job_free(&job_list, &last, &start);
		else
		{
			job_list->j->id = ++i;
			last = job_list;
			job_list = job_list->next;
		}
	}
	replace_plus_and_minus(start);
	if (copy != NULL && lenlist(start, NULL, 1) == lenlist(NULL, copy, 0))
		return_to_the_copy(start, copy);
	repare_plus_and_minus(start, 0, 0);
	stock(start, 9);
}

void		print_job(t_job *j)
{
	t_process	*process;

	ft_printf("[%d] %c %d	", j->id, j->current, j->pgid);
	if (j->status == 'f')
		ft_printf("Done	");
	else if (j->status == 's')
		ft_printf("Stopped	");
	else
		ft_printf("Running	");
	process = j->p;
	print_complete_process(j->p);
}

int			find_job_pgid(pid_t pgid)
{
	t_job_list	*job_list;

	job_list = stock(NULL, 10);
	if (job_list == NULL)
		return (-1);
	while (job_list)
	{
		if (job_list->j->pgid == pgid)
			return (job_list->j->id);
		job_list = job_list->next;
	}
	return (-1);
}
