/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_bis.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/07 18:48:34 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 15:45:31 by vde-sain    ###    #+. /#+    ###.fr     */
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
