/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key_struct.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 10:50:36 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 10:33:53 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static void		init_t_htab(t_htab *htab)
{
	htab->content = NULL;
	htab->content_no = 0;
	htab->content_type = -1;
	htab->lenght_max = 0;
	htab->matching_index = -1;
	htab->next = NULL;
	htab->prev = NULL;
}

t_htab			*add_list_back_sort_htab(t_htab *head, t_htab *ls, int loop)
{
	t_htab	*tmp;

	tmp = NULL;
	if (loop == 0)
	{
		ls->next = NULL;
		return (ls);
	}
	tmp = head;
	while (head->next != NULL)
		head = head->next;
	head->next = ls;
	ls->next = NULL;
	ls->prev = head;
	return (tmp);
}

t_htab			*add_list_back_htab(t_htab *htab)
{
	t_htab	*new;

	new = NULL;
	if (!(new = (t_htab*)malloc(sizeof(t_htab))))
		return (NULL);
	if (htab == NULL)
	{
		init_t_htab(new);
		return (new);
	}
	else
	{
		while (htab->next != NULL)
			htab = htab->next;
		init_t_htab(new);
		new->prev = htab;
		htab->next = new;
		return (new);
	}
	free(new);
	return (NULL);
}

void			free_htab(t_htab *htab)
{
	t_htab	*tmp;

	if (htab == NULL)
		return ;
	while (htab->prev)
		htab = htab->prev;
	tmp = htab;
	while (htab)
	{
		htab = htab->next;
		free(tmp->content);
		free(tmp);
		tmp = htab;
	}
}

t_htab			*fill_new_htab(t_htab *htab, t_htab *new, int match)
{
	new = add_list_back_htab(new);
	new->content = ft_strdup(htab->content);
	new->content_type = htab->content_type;
	new->lenght_max = ft_strlen(new->content);
	new->content_no = new->prev == NULL ? 0 : new->prev->content_no + 1;
	new->matching_index = match;
	if (new->prev == NULL)
		new->lenght_max = ft_strlen(new->content);
	else
		new->lenght_max = new->lenght_max > new->prev->lenght_max ?
	ft_strlen(new->content) : new->prev->lenght_max;
	return (new);
}
