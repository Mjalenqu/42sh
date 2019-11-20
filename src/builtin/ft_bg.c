/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bg.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 16:44:23 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"
#include "../../includes/exec.h"

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

static t_job	*iterate_through_list(t_job_list *jb, char *ans)
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
			return (jb->j);
		}
		ft_strdel(&name);
		jb = jb->next;
	}
	ft_printf_err_fd("42sh: bg: %s: no such job\n", ans);
	return (NULL);
}

t_job			*find_job_by_id_bg(char **cmd, int i)
{
	t_job		*j;
	t_job		*save;
	t_job_list	*jb;
	int			check;

	check = 0;
	j = NULL;
	save = NULL;
	jb = stock(NULL, 10);
	if (cmd[i] == NULL)
		return (find_plus(jb));
	while (cmd[i])
	{
		save = iterate_through_list(jb, cmd[i++]);
		if (save)
		{
			check = 0;
			j = save;
		}
	}
	if (check != 0)
		return (NULL);
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
		ft_printf_err_fd("42sh: bg: no such job\n", p->fd_out);
	var = NULL;
	return (1);
}
