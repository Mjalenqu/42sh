/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_jobs.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:08:12 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 10:33:25 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

pid_t			get_pid_fg(t_process *p)
{
	pid_t	save;

	save = p->pid;
	while (p)
	{
		if (kill(p->pid, 0) == 0)
		{
			save = p->pid;
			break ;
		}
		p = p->next;
	}
	return (save);
}

int				ft_jobs_option(char **cmd, int *i)
{
	int			j;
	int			ret;

	ret = 0;
	while (cmd[*i] && cmd[*i][0] == '-')
	{
		j = 1;
		if (ft_strcmp(cmd[*i], "--") == 0)
			return (ret);
		while (cmd[*i][j])
		{
			if (cmd[*i][j] == 'p')
				ret = 'p';
			else if (cmd[*i][j] == 'l')
				ret = 'l';
			else
				return (cmd[*i][j]);
			j++;
		}
		*i += 1;
	}
	return (ret);
}

char			*built_job_name(t_job_list *j, char *name)
{
	int			i;
	t_process	*tmp;

	tmp = j->j->p;
	i = 0;
	while (tmp && kill(tmp->pid, 0) == -1)
		tmp = tmp->next;
	if (tmp == NULL)
	{
		ft_strdel(&name);
		return (NULL);
	}
	while (tmp->cmd[i])
	{
		name = ft_strjoinf(name, tmp->cmd[i], 1);
		if (tmp->cmd[i + 1])
			name = ft_strjoinf(name, " ", 1);
		i++;
	}
	return (name);
}

int				ft_jobs(t_process *p, t_var **var)
{
	t_job_list	*job_list;
	int			option;
	int			i;

	(void)var;
	i = 1;
	option = ft_jobs_option(p->cmd, &i);
	if (option != 'l' && option != 'p' && option != 0)
	{
		ft_printf_err_fd("42sh: jobs: -%c: invalid option\n", option);
		ft_printf_err_fd("jobs: usage: jobs [-l|-p] [job_id...]\n");
		return (2);
	}
	job_list = stock(NULL, 10);
	if (p->cmd[i] == NULL)
		print_all_jobs(job_list, option);
	while (p->cmd[i])
		print_selected_jobs(job_list, option, p->cmd[i++]);
	return (0);
}
