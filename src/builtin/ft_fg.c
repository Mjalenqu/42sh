/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fg.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:44:48 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 10:54:06 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"
#include "../../includes/builtin.h"

void			put_foreground(t_job *j, t_var **var, t_process *p)
{
	pid_t		tmp;
	t_pos		*pos;

	pos = to_stock(NULL, 1);
	pos->last_cmd_on_bg = 1;
	tmp = get_pid_fg(j->p);
	kill(tmp, SIGCONT);
	j->status = 'r';
	tcsetpgrp(0, j->pgid);
	wait_process(var);
	signal(SIGTTOU, SIG_IGN);
	if (p->background == 0)
		tcsetpgrp(0, getpid());
	else
		tcsetpgrp(0, p->pid);
	signal(SIGTTOU, SIG_DFL);
}

int				rerun_job(t_job *j, t_var **var, t_process *p)
{
	put_foreground(j, var, p);
	return (0);
}

void			replace_minus_by_plus(t_job_list *save)
{
	while (save)
	{
		if (save->j->current == '-')
		{
			save->j->current = '+';
			save->j->was_a_plus = 0;
		}
		save = save->next;
	}
}

t_job			*find_job_by_id(char *argv)
{
	int			pid;
	t_job_list	*job_list;
	char		*name;
	t_job_list	*save;

	job_list = stock(NULL, 10);
	pid = ft_atoi(argv);
	name = ft_strnew(0);
	save = job_list;
	while (job_list)
	{
		name = built_job_name(job_list, name);
		if (job_list->j->pgid == pid || job_list->j->id == pid ||
				ft_strncmp(name, argv, ft_strlen(argv)) == 0)
		{
			move_plus_and_minus_indicators(job_list, save);
			ft_strdel(&name);
			return (job_list->j);
		}
		ft_strdel(&name);
		job_list = job_list->next;
	}
	return (NULL);
}

int				ft_fg(t_process *p, t_var **var)
{
	t_job		*job;

	if (ft_tabclen(p->cmd) <= 1)
	{
		job = find_plus(stock(NULL, 10));
		move_plus_and_minus_indicators(find_plus_jb(stock(NULL, 10)),
			stock(NULL, 10));
		if (job != NULL)
			return (rerun_job(job, var, p));
		else
			ft_printf_err_fd("fg: current: no such job\n", p->fd_out);
	}
	else
	{
		job = find_job_by_id(p->cmd[1]);
		if (job != NULL)
			return (rerun_job(job, var, p));
		else
			ft_printf_err_fd("fg: job not found\n");
	}
	return (1);
}
