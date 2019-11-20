/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_tool.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 17:37:07 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 18:01:09 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/lexeur.h"

int				cnt_process(t_lexeur **res, int i)
{
	int		nb;

	nb = 0;
	while (res[i])
	{
		if (res[i]->word)
			nb++;
		i++;
	}
	return (nb);
}

void			change_job(t_job **j, t_process **start)
{
	(*j)->p->next = NULL;
	(*j)->p = *start;
	(*j) = (*j)->next;
	(*j)->p = ft_malloc(sizeof(t_process));
	*start = (*j)->p;
}

int				check_moove_index(t_lexeur **res, int *t)
{
	while (res[*t] && res[*t]->word)
		(*t)++;
	if (res[*t] && (res[*t]->token != 4 && res[*t]->token != 5 &&
	res[*t]->token != 8 && res[*t]->token != 6 && res[*t]->token != 9
	&& res[*t]->token != 7))
		return (1);
	return (0);
}

t_redirect		*init_var(int *t, int *i)
{
	(*t) = *i;
	return (NULL);
}

int				check_token_in_condition(t_lexeur **res, int t)
{
	if (res[t] && (res[t]->token == 4 || res[t]->token == 5 ||
	res[t]->token == 8 || res[t]->token == 6 || res[t]->token == 7 ||
	res[t]->token == 9))
		return (1);
	return (0);
}
