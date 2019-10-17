/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_jobs.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:08:12 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/11 15:30:06 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

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

	i = 0;
	while (j->j->p->cmd[i])
	{
		name = ft_strjoinf(name, j->j->p->cmd[i], 1);
		if (j->j->p->cmd[i + 1])
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
		ft_printf_err("42sh: jobs: -%c: invalid option\n", option);
		ft_printf_err("jobs: usage: jobs [-l|-p] [job_id...]\n");
		return (2);
	}
	job_list = stock(NULL, 10);
	if (p->cmd[i] == NULL)
		print_all_jobs(job_list, option);
	while (p->cmd[i])
		print_selected_jobs(job_list, option, p->cmd[i++]);
	return (0);
}
