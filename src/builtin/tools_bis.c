/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_bis.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 18:48:34 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/07 18:49:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "builtin.h"

void		free_new_env(t_var *head)
{
	t_var	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		tmp->data = ft_secure_free(tmp->data);
		tmp->name = ft_secure_free(tmp->name);
		free(tmp);
	}
}
