/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bg.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:44:23 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 09:14:16 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"
#include "../../includes/exec.h"

void			put_background(t_job *j)
{
	kill(-j->pgid, SIGCONT);
}

char			*find_split_process(t_process *p)
{
	if (p->split == 'A')
		return (" && ");
	else if (p->split == '|')
		return (" || ");
	else if (p->split == 'P')
		return (" | ");
	else
		return ("");
}

static void		iterate_through_list(t_job_list *jb, char *ans)
{
	char		*name;
	t_job_list	*save;

	save = jb;
	name = ft_strnew(0);
	while (jb)
	{
		name = built_job_name(jb, name);
		if (jb->j->id == ft_atoi(ans) ||
		ft_strncmp(name, ans, ft_strlen(ans)) == 0)
		{
			change_plus_and_minus_indicators(jb, find_plus(save), save);
			ft_strdel(&name);
			return ;
		}
		ft_strdel(&name);
		jb = jb->next;
	}
	ft_printf_err("42sh: bg: %s: no such job\n", ans);
}

t_job			*find_job_by_id_bg(char **cmd, int i)
{
	t_job		*j;
	t_job_list	*jb;

	jb = stock(NULL, 10);
	j = find_plus(jb);
	if (cmd[i] == NULL)
		return (j);
	while (cmd[i])
		iterate_through_list(jb, cmd[i++]);
	return (j);
}

int				ft_bg(t_process *p, t_var **var)
{
	t_job		*job;
	t_pos		*pos;
	t_save_job	*copy;

	job = find_job_by_id_bg(p->cmd, 1);
	if (job != NULL)
	{
		pos = to_stock(NULL, 1);
		pos->last_cmd_on_bg = 1;
		kill(-job->pgid, SIGCONT);
		job->status = 'r';
		copy = stock_t_job(NULL, 3);
		free_copy_job(copy);
		copy = copy_job_list(stock(NULL, 10), NULL);
		stock_t_job(copy, 2);
		return (0);
	}
	else if (p->cmd[1] == NULL)
		ft_printf_err("42sh: bg: no such job\n", p->fd_out);
	var = NULL;
	return (1);
}
