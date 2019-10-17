/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key_sort.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 17:37:25 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/22 15:09:50 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static int		sort_by_ascii(t_htab *tmp, t_htab *tmp2)
{
	if (ft_strcmp(tmp->content, tmp2->content) <= 0)
		return (1);
	return (0);
}

static void		generic_sort_list_3(t_htab **ls, t_htab **tmp)
{
	if (*tmp && *tmp == *ls)
		*ls = (*ls)->next;
	else
		(*tmp)->prev->next = (*tmp)->next;
	if ((*tmp)->next == *ls)
		(*tmp)->prev = NULL;
	else if ((*tmp)->next != NULL)
		(*tmp)->next->prev = (*tmp)->prev;
}

static void		generic_sort_list_2(t_htab **tmp, t_htab **tmp2)
{
	while (*tmp2)
	{
		if (sort_by_ascii(*tmp, *tmp2) == 0)
			*tmp = *tmp2;
		*tmp2 = (*tmp2)->next;
	}
}

static t_htab	*generic_sort_list(t_htab *head, t_htab *ls, int loop)
{
	t_htab	*tmp;
	t_htab	*tmp2;

	ls = head;
	tmp = ls;
	tmp2 = tmp;
	while (ls)
	{
		generic_sort_list_2(&tmp, &tmp2);
		if (ls->next == NULL)
		{
			head = add_list_back_sort_htab(head, ls, loop);
			ls = NULL;
		}
		else
		{
			generic_sort_list_3(&ls, &tmp);
			head = add_list_back_sort_htab(head, tmp, loop++);
			tmp = ls;
			tmp2 = tmp->next;
		}
	}
	return (head);
}

t_htab			*sort_list_htab(t_htab *head)
{
	t_htab	*ls_sort;

	ls_sort = NULL;
	if (head)
		head = generic_sort_list(head, ls_sort, 0);
	ls_sort = head;
	while (ls_sort)
	{
		ls_sort->content_no = ls_sort->prev == NULL ?
			0 : ls_sort->prev->content_no + 1;
		ls_sort = ls_sort->next;
	}
	head->prev = NULL;
	return (head);
}
