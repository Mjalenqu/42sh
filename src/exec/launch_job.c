/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_job.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/29 18:52:00 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 14:33:50 by vde-sain    ###    #+. /#+    ###.fr     */
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
			alert_job(j);
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
	before_redirection(p);
	*infile = 0;
	return (p);
}

void		launch_simple_job(t_process *p, t_job *j, t_var **var)
{
	p->fd_out = 1;
	fork_simple(j, p, var, NULL);
}

void		launch_job(t_job *j, t_var *var)
{
	t_process	*p;
	int			infile;
	int			mypipe[2];

	p = init_launch_job(j, &infile);
	while (p)
	{
		if (check_process(var, p, j))
			return (free_temp(&var));
		p->fd_in = infile;
		if (p->split == 'P')
		{
			pipe(mypipe);
			p->fd_out = mypipe[1];
			fork_simple(j, p, &var, NULL);
			close(mypipe[1]);
			infile = mypipe[0];
		}
		else
			launch_simple_job(p, j, &var);
		p = get_and_or(p);
		free_temp(&var);
	}
	alert_job(j);
}
