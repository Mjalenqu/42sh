/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job_function_plus_and_minus.c                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 16:55:55 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 10:17:28 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

t_save_job	*stock_t_job(t_save_job *stock, int usage)
{
	static t_save_job	*copy = NULL;

	if (usage == 2)
		copy = stock;
	else if (usage == 3)
		return (copy);
	return (NULL);
}

int			place_minus_before_plus_check_null(t_job_list *save, int check)
{
	if (save && check == 0 && save->j->current == '+')
	{
		if (save->next == NULL)
			return (1);
		while (save->next)
			save = save->next;
		save->j->current = '-';
		save->j->was_a_plus = 1;
		return (1);
	}
	else if (check == 0)
	{
		while (save)
		{
			if (save->next && save->next->j->current == '+')
			{
				save->j->current = '-';
				save->j->was_a_plus = 1;
			}
			save = save->next;
		}
		return (1);
	}
	return (0);
}

int			place_minus_before_plus(t_job_list *save)
{
	t_job_list	*tmp;
	int			check;

	check = 0;
	tmp = save;
	while (tmp)
	{
		if (tmp->j->current == '-')
			check = 1;
		tmp = tmp->next;
	}
	return (place_minus_before_plus_check_null(save, check));
}

void		replace_plus_and_minus(t_job_list *start)
{
	int			check;
	t_job_list	*tmp;

	check = 0;
	tmp = start;
	check = place_minus_before_plus(start);
	start = tmp;
	while (start && check == 0)
	{
		if (start->j->current == '-')
			start->j->current = '+';
		if (start->j->was_a_plus == 1)
			start->j->current = '-';
		start = start->next;
	}
}

int			lenlist(t_job_list *start, t_save_job *copy, int usage)
{
	int		i;

	i = 0;
	if (usage == 1)
	{
		while (start)
		{
			i += 1;
			start = start->next;
		}
		return (i);
	}
	else if (usage == 0)
	{
		while (copy)
		{
			i += 1;
			copy = copy->next;
		}
		return (i);
	}
	return (0);
}
