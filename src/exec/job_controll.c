/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_controll.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/21 14:45:30 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/14 16:16:05 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

void		process_status(t_process *process, t_job_list *job_list, int status,
			t_var **var)
{
	if (WIFSTOPPED(status))
	{
		job_list->j->status = 's';
		process->stoped = STOPED;
		job_list->j->notified = 1;
		print_job(job_list->j);
	}
	else
	{
		if (WIFSIGNALED(status))
			ft_printf_err("terminated by signal %d\n", WTERMSIG(status));
		job_list->j->status = 'f';
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

void		print_start_process(t_job *j)
{
	t_process	*p;

	p = j->p;
	ft_printf("[%d]", j->id);
	while (p)
	{
		ft_printf(" %d", p->pid);
		p = p->next;
	}
	ft_putchar('\n');
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
