/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_job.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:43:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 15:34:59 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

t_save_job		*add_list_save_job(t_job *save, t_save_job *chain)
{
	t_save_job	*new;

	new = NULL;
	if (!(new = (t_save_job*)ft_malloc(sizeof(t_save_job))))
		return (NULL);
	if (chain == NULL)
	{
		new->current = save->current;
		new->was_a_plus = save->was_a_plus;
		new->prev = NULL;
		new->next = NULL;
		return (new);
	}
	while (chain->next != NULL)
		chain = chain->next;
	new->current = save->current;
	new->was_a_plus = save->was_a_plus;
	new->next = NULL;
	new->prev = chain;
	chain->next = new;
	return (new);
}

t_save_job		*copy_job_list(t_job_list *save, t_save_job *head)
{
	t_save_job	*chain;

	chain = NULL;
	while (save)
	{
		if (chain == NULL)
		{
			head = add_list_save_job(save->j, chain);
			chain = head;
		}
		else
			chain = add_list_save_job(save->j, chain);
		save = save->next;
	}
	return (head);
}

t_job_list		*new_job(t_job *j, int number)
{
	t_job_list	*job_list;

	if (!(job_list = ft_malloc(sizeof(t_job_list))))
		return (NULL);
	j->id = number;
	job_list->j = j;
	job_list->j->current = ' ';
	job_list->next = NULL;
	return (job_list);
}

void			free_copy_job(t_save_job *copy)
{
	t_save_job	*tmp;

	tmp = NULL;
	while (copy)
	{
		tmp = copy;
		copy = copy->next;
		free(tmp);
	}
	stock_t_job(NULL, 2);
}

void			add_job(t_job *j, int i)
{
	t_job_list	*job_list;
	t_job_list	*start;
	t_save_job	*copy;

	copy = stock_t_job(NULL, 3);
	start = stock(NULL, 10);
	free_copy_job(copy);
	copy = copy_job_list(start, NULL);
	stock_t_job(copy, 2);
	if (start == NULL)
	{
		start = new_job(j, 1);
		start->j->current = '+';
	}
	else
	{
		i = 2;
		job_list = start;
		while (job_list->next != NULL && i++)
			job_list = job_list->next;
		job_list->next = new_job(j, i);
		place_plus_and_minus(start, job_list->next->j->split);
		job_list->next->j->current = '+';
	}
	stock(start, 9);
}
