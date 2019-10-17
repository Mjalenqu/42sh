/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 14:34:20 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/16 13:20:31 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/lexeur.h"

t_redirect		*fill_agregator(t_redirect *p, t_lexeur **res, int *i, int t)
{
	int			done;
	t_redirect	*tmp;

	tmp = init_var(&done, &t, i);
	while (res[t])
	{
		if (check_moove_index(res, &t))
			break ;
		if (res[t] && (check_token_in_condition(res, t)))
		{
			done += (res[t]->token == 7) ? 1 : 0;
			if (!tmp)
			{
				tmp = malloc(sizeof(t_redirect));
				p = tmp;
				(*i) += fill_ag_first(tmp, res, &t);
			}
			else
				(*i) += fill_ag_next(tmp, res, &t);
			done++;
		}
		t += (res[t]) ? 1 : 0;
	}
	(*i) += done;
	return (p);
}

void			fill_cmd(t_lexeur **res, t_job **j, int *k, int *i)
{
	(*j)->p->cmd[*k] = ft_strdup(res[*i]->word);
	(*k)++;
	(*i)++;
}

void			fill_process_first_part(t_job **j, t_lexeur **res,
int *i, int k)
{
	if (res[*i]->token == 7)
	{
		(*j)->p->cmd = NULL;
		return ;
	}
	(*j)->p->cmd = malloc(sizeof(char *) * (cnt_process(res, *i) + 1));
	while (res[*i] && res[*i]->word)
		fill_cmd(res, j, &k, i);
	fill_all_cmd(res, j, &k, *i);
	(*j)->p->cmd[k] = NULL;
	(*j)->p->builtin = test_builtin((*j)->p);
}

int				fill_process_while(t_lexeur **res, t_job **j, t_process **start,
int *i)
{
	int		k;

	k = 0;
	fill_process_first_part(j, res, i, k);
	if (res[*i])
		(*j)->p->redirect = fill_agregator(NULL, res, i, 0);
	if (res[*i] && (res[*i]->token == 0 || res[*i]->token == 2
	|| res[*i]->token == 3))
	{
		fill_process_split(j, res, *i);
		(*j)->p->next = malloc(sizeof(t_process));
		(*j)->p = (*j)->p->next;
		(*j)->p->status = '\0';
	}
	else if ((res[*i] && (*j)->next != NULL) && (res[*i]->token == 1 ||
	res[*i]->token == 10))
		change_job(j, start);
	else
	{
		(*j)->p->next = NULL;
		(*j)->p = *start;
		return (0);
	}
	return (1);
}

void			fill_process(t_job *j, t_lexeur **res)
{
	int			i;
	t_process	*start;

	i = 0;
	j->p = malloc(sizeof(t_process));
	start = j->p;
	while (res[i])
	{
		j->p->status = '\0';
		j->p->stoped = 0;
		j->p->completed = 0;
		j->p->redirect = NULL;
		j->p->split = '\0';
		if (fill_process_while(res, &j, &start, &i) == 0)
			break ;
		i++;
	}
}
