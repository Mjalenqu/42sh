/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alias_norme.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 10:32:11 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 10:32:30 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	free_one(t_var *var)
{
	ft_strdel(&var->data);
	ft_strdel(&var->name);
	free(var);
}
