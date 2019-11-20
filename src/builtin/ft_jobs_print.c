/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_jobs_print.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:02:51 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 10:33:39 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void			print_complete_process(t_process *p)
{
	int		i;

	while (p)
	{
		i = 0;
		while (p->next && p->completed == 1)
			p = p->next;
		while (p->cmd[i])
			ft_printf("%s ", p->cmd[i++]);
		p->printed = 1;
		if (p->next)
		{
			if (p->split == 'A')
				ft_printf("&& ");
			if (p->split == '|')
				ft_printf("|| ");
			if (p->split == 'P')
				ft_printf("| ");
		}
		p = p->next;
	}
	ft_putchar('\n');
}

void			print_status_job(char status)
{
	if (status == 'f')
		ft_printf_fd("Done	");
	else if (status == 's')
		ft_printf_fd("Stopped	");
	else
		ft_printf_fd("Running	");
}

void			print_current_job(t_job_list *j, int option)
{
	if (option != 'p')
		ft_printf_fd("[%d]%c ", j->j->id, j->j->current);
	if (option == 'p' || option == 'l')
		ft_printf_fd("%d ", j->j->pgid);
	if (option != 'p')
	{
		print_status_job(j->j->status);
		print_complete_process(j->j->p);
	}
}

void			print_all_jobs(t_job_list *j, int option)
{
	while (j)
	{
		print_current_job(j, option);
		j = j->next;
	}
}

void			print_selected_jobs(t_job_list *j, int option, char *arg)
{
	char		*name;
	int			check;

	check = 0;
	while (j)
	{
		name = ft_strnew(0);
		name = built_job_name(j, name);
		if (name && (ft_strncmp(name, arg, ft_strlen(arg)) == 0
		|| j->j->id == ft_atoi(arg)))
		{
			print_current_job(j, option);
			check += 1;
		}
		j = j->next;
		ft_strdel(&name);
	}
	if (!check)
		ft_printf_err_fd("42sh: jobs: %s: no such job\n", arg);
	if (name)
		ft_strdel(&name);
}
