/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_job_process.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/29 18:52:00 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 10:27:31 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

t_process	*get_and_or(t_process *p)
{
	if (p->split != '|' && p->split != 'A')
		return (p->next);
	if (p->split == '|' && p->ret != 0)
		return (p->next);
	else if (p->split == 'A' && p->ret == 0)
		return (p->next);
	return (p->next->next);
}

void		alert_job(t_job *j)
{
	if (j->split != '&' && is_builtin_modify(j->p))
	{
		free_job(j);
		return ;
	}
	if (j->split == '&')
		print_start_process(j);
	else if (job_is_stoped(j))
		j->notified = 1;
	else
		remove_job(j->id, 0);
}
