/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_notification.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:43:45 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 10:27:41 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

void		update_status(t_var **var)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status(pid, status, var))
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	}
}

int			job_is_completed(t_job *j)
{
	t_process	*p;

	p = j->p;
	while (p)
	{
		if (p->completed == 0)
			return (0);
		p = p->next;
	}
	return (1);
}

int			job_is_stoped(t_job *j)
{
	t_process	*p;

	p = j->p;
	while (p)
	{
		if (p->stoped == 0)
		{
			return (0);
		}
		p = p->next;
	}
	return (1);
}

t_job_list	*job_notification_while(t_job_list *job_list, t_job_list **last)
{
	t_job_list *next;

	next = job_list->next;
	if (job_is_completed(job_list->j))
	{
		print_job(job_list->j);
		remove_job(job_list->j->id, 0);
		return (NULL);
	}
	else if (job_is_stoped(job_list->j) && !job_list->j->notified)
	{
		job_list->j->notified = 1;
		print_job(job_list->j);
		*last = job_list;
	}
	else
		*last = job_list;
	return (next);
}

void		job_notification(t_var **var)
{
	t_job_list	*job_list;
	t_job_list	*last;
	t_job_list	*first_job;

	last = NULL;
	update_status(var);
	first_job = stock(NULL, 10);
	job_list = first_job;
	while (job_list)
	{
		if ((job_list = job_notification_while(job_list, &last)) == NULL)
			return ;
	}
	stock(first_job, 9);
}
