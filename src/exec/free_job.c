/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_job.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 14:45:30 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 08:26:26 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void		free_job_list(void)
{
	t_job_list	*job_list;

	if ((job_list = stock(NULL, 10)) == NULL)
		return ;
	while (job_list)
	{
		kill(job_list->j->pgid, SIGINT);
		free_job(job_list->j);
		job_list = job_list->next;
	}
}

void		free_redirections(t_redirect *ptr_redi)
{
	t_redirect *r;
	t_redirect *next;

	r = ptr_redi;
	while (r)
	{
		if (ft_strcmp(r->token, "<<") == 0)
			ft_strdel(&r->heredoc_content);
		else
		{
			if (r->fd_out)
				ft_strdel(&r->fd_out);
			if (r->fd_in)
				ft_strdel(&r->fd_in);
			if (r->token)
				ft_strdel(&r->token);
		}
		next = r->next;
		free(r);
		r = next;
	}
}

void		free_process(t_process *ptr_p)
{
	t_process *p;
	t_process *next;

	p = ptr_p;
	while (p)
	{
		if (p->cmd)
			ft_free_tab(p->cmd);
		if (p->redirect)
			free_redirections(p->redirect);
		next = p->next;
		free(p);
		p = next;
	}
}

void		free_job(t_job *j)
{
	free_process(j->p);
	free(j);
}
