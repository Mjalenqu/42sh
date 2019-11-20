/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_job.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 14:45:30 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 09:55:11 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void		free_process_in_job(t_process *process, int i)
{
	i = 0;
	if (kill(process->pid, 0) == 0)
	{
		ft_printf_fd("job killed: %d -", process->pid);
		while (process->cmd[i])
			ft_printf_fd(" %s", process->cmd[i++]);
		ft_printf_fd("\n");
		kill(process->pid, SIGKILL);
	}
}

void		free_job_list(int i)
{
	t_job_list	*job_list;
	t_job_list	*tmp;
	t_process	*process;

	if ((job_list = stock(NULL, 10)) == NULL)
		return ;
	while (job_list)
	{
		tmp = job_list->next;
		process = job_list->j->p;
		while (process)
		{
			free_process_in_job(process, i);
			process = process->next;
		}
		free_job(job_list->j);
		free(job_list);
		job_list = tmp;
	}
	stock(NULL, 9);
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
		if (p->fd_in)
			close(p->fd_in);
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
	j = NULL;
}
