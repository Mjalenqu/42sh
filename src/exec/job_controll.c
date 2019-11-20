/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_controll.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 14:45:30 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:01:56 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

int			process_printed(t_process *p)
{
	while (p)
	{
		if (p->printed == 1)
			return (1);
		p = p->next;
	}
	return (0);
}

void		process_status(t_process *process, t_job_list *job_list, int status,
			t_var **var)
{
	if (WIFSTOPPED(status))
	{
		job_list->j->status = 's';
		process->stoped = STOPED;
		job_list->j->notified = 1;
		if (process_printed(job_list->j->p) == 0)
			print_job(job_list->j);
	}
	else
	{
		if (WIFSIGNALED(status))
			ft_printf_err("Terminated by signal %d\n", status);
		process->completed = FINISHED;
		process->ret = WEXITSTATUS(status);
		add_list_env(var, SPE, ft_strdup("?"), ft_itoa(process->ret));
	}
}

int			mark_process_status(pid_t pid, int status, t_var **var)
{
	t_job_list	*job_list;
	t_process	*process;

	job_list = stock(NULL, 10);
	if (pid > 0)
	{
		while (job_list)
		{
			process = job_list->j->p;
			while (process)
			{
				if (process->pid == pid)
				{
					process->status = status;
					process_status(process, job_list, status, var);
					return (0);
				}
				process = process->next;
			}
			job_list = job_list->next;
		}
	}
	return (-1);
}

void		wait_process(t_var **var)
{
	int			status;
	pid_t		pid_test;

	pid_test = waitpid(WAIT_ANY, &status, WUNTRACED);
	mark_process_status(pid_test, status, var);
}

void		wait_process_pid(int pid, t_var **var)
{
	int			status;
	pid_t		pid_test;

	pid_test = waitpid(pid, &status, WUNTRACED);
	mark_process_status(pid_test, status, var);
}
