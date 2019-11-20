/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_job.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/29 18:52:00 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 15:35:58 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

int			check_process(t_var *var, t_process *p, t_job *j)
{
	if (p->cmd && p->cmd[0] && find_equal(p->cmd[0]) == 1)
	{
		if ((p->cmd = check_exec_var(p->cmd, &var)) == NULL)
		{
			if (!p->next)
			{
				alert_job(j);
				return (2);
			}
			return (1);
		}
	}
	return (0);
}

t_process	*init_launch_job(t_job *j, int *infile)
{
	t_process *p;

	p = j->p;
	if (!(j->split != '&' && is_builtin_modify(p)))
		add_job(j, 2);
	j->status = 'r';
	*infile = 0;
	return (p);
}

int			launch_multiple_jobs(t_process *p, t_job *j, t_var **var,
			int *mypipe)
{
	pipe(mypipe);
	p->fd_out = mypipe[1];
	fork_simple(j, p, var, NULL);
	close(mypipe[1]);
	return (mypipe[0]);
}

void		send_job_to_fork_simple(t_process *p, t_job *j, t_var *var,
			int *infile)
{
	int		mypipe[2];
	t_pos	*pos;

	pos = to_stock(NULL, 1);
	if (!p || !p->cmd)
		return ;
	p->fd_in = *infile;
	if (p->split == 'P')
	{
		pipe(mypipe);
		p->fd_out = mypipe[1];
		fork_simple(j, p, &var, NULL);
		pos->pipe = p->fd_out;
		close(mypipe[1]);
		*infile = mypipe[0];
	}
	else
	{
		p->fd_out = 1;
		fork_simple(j, p, &var, NULL);
	}
}

void		launch_job(t_job *j, t_var *var, t_pos *pos, t_process *p)
{
	int			infile;
	int			ret;

	pos->pipe = 0;
	p = init_launch_job(j, &infile);
	while (p && pos->exit_mode == -100)
	{
		pos->act_fd_out = 1;
		pos->act_fd_error = 2;
		if ((ret = check_process(var, p, j)) == 1)
			free_temp(&var);
		else if (ret == 2)
			return (free_temp(&var));
		else
			send_job_to_fork_simple(p, j, var, &infile);
		if (p->fd_in == 250)
		{
			ft_printf_err("42sh: error: Too many pipes\n");
			break ;
		}
		p = get_and_or(p);
		if (pos->exit_mode < 0)
			free_temp(&var);
	}
	alert_job(j);
}
