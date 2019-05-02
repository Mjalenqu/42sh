/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/18 13:43:41 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 13:11:45 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/lexeur.h"

void		print_job(t_job *j)
{
	int		job;
	int		i;
	int		process;
	t_process	*start;

	job = 0;
	i = 0;
	process = 0;
	while (j)
	{
		printf("\n---jobs---[%d]->next: _%p_\tsplit: _%c_\n", job, j->next, j->split);
		job++;
		start = j->p;
		while (j->p)
		{
			printf("--process--[%d]->next: _%p_\tsplit:_%c_\ttoken: |%c|\n", process, j->p->next, j->p->split, j->p->split);
			process++;
			while (j->p->cmd[i])
			{
				printf("cmd[%d]-> _%s_\n", i, j->p->cmd[i]);
				i++;
			}
			i = 0;
			j->p = j->p->next;
		}
		j->p = start;
		process = 0;
		j = j->next;
	}
}

void		init_job(t_job *j)
{
	j->split = '\0';
	j->status = '\0';
}

void		fill_job(t_job *j, t_lexeur **res)
{
	int			i;
	int			k;

	i = 0;
	k = 0;
	while (res[i])
	{
		if (res[i]->token == 1 || res[i]->token == 8)
		{
			if (res[i]->token == 1)
				j->split = '&';
			else
				j->split = ';';
			if (res[i + 1])
			{
				j->next = malloc(sizeof(t_job));
				j = j->next;
				init_job(j);
			}
		}
		if (res[i])
			i++;
	}
	j->next = NULL;
}

int			start_exec(t_lexeur **res)
{
	t_job		*j;

	j = malloc(sizeof(t_job));
	init_job(j);
	fill_job(j, res);
	fill_process(j, res);
	print_job(j);
	return (0);
}
