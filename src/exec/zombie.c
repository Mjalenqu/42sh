/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zombie.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/08 12:18:10 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 14:20:33 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

t_pid_launch	*have_a_zombie(t_pid_launch *spid, t_pid_launch **head_spid,
				t_pid_launch *tmp)
{
	if (kill(spid->pid, 0) == 0)
		kill(spid->pid, 9);
	if (spid->prev == NULL)
	{
		*head_spid = spid->next;
		if (*head_spid != NULL)
			(*head_spid)->prev = NULL;
		free(spid);
		spid = *head_spid;
		to_stock(spid, 6);
	}
	else
	{
		spid = spid->prev;
		tmp = spid->next->next;
		free(spid->next);
		if (tmp != NULL)
			tmp->prev = spid;
		spid->next = tmp;
		spid = tmp;
	}
	return (spid);
}

void			kill_zombie(t_pid_launch *spid, t_job_list *jb)
{
	t_job_list		*head_jb;
	t_pid_launch	*head_spid;
	t_pid_launch	*tmp;
	int				check;

	head_jb = jb;
	head_spid = spid;
	tmp = NULL;
	while (spid)
	{
		jb = head_jb;
		check = 0;
		while (jb)
		{
			if (jb->j->p->pid == spid->pid)
				check = 1;
			jb = jb->next;
		}
		if (check != 1)
			spid = have_a_zombie(spid, &head_spid, tmp);
		else
			spid = spid->next;
	}
}

t_pid_launch	*add_list_back_pid_launch(t_pid_launch *spid, int pid)
{
	t_pid_launch	*new;

	new = NULL;
	if (!(new = (t_pid_launch*)ft_malloc(sizeof(t_pid_launch))))
		return (NULL);
	if (spid == NULL)
	{
		new->next = NULL;
		new->pid = pid;
		new->prev = NULL;
		return (new);
	}
	while (spid->next != NULL)
		spid = spid->next;
	new->next = NULL;
	new->pid = pid;
	new->prev = spid;
	spid->next = new;
	return (new);
}

void			remember_pid(int pid)
{
	t_pid_launch	*spid;
	t_pid_launch	*head;

	head = to_stock(NULL, 7);
	spid = add_list_back_pid_launch(head, pid);
	if (head == NULL)
		to_stock(spid, 6);
}

void			free_pid_launch(void)
{
	t_pid_launch	*spid;
	t_pid_launch	*tmp;

	spid = to_stock(NULL, 7);
	while (spid)
	{
		tmp = spid;
		spid = spid->next;
		free(tmp);
	}
}
