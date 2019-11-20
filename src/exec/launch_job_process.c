/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_job_process.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/29 18:52:00 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/05 19:32:10 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

t_process	*get_and_or(t_process *p)
{
	char split;

	if (p->split != '|' && p->split != 'A')
		return (p->next);
	split = p->split;
	if (p->split == '|' && p->ret != 0)
		return (p->next);
	else if (p->split == 'A' && p->ret == 0)
		return (p->next);
	while (p)
	{
		if (p->split != split)
			return (p->next);
		p = p->next;
	}
	return (NULL);
}

void		alert_job(t_job *j)
{
	if (j->split != '&' && is_builtin_modify(j->p))
	{
		free_job(j);
		return ;
	}
	if (j->split != '&' && job_is_stoped(j))
		j->notified = 1;
	else if (j->split != '&')
		remove_job(j->id, 0);
}
