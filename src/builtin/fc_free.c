/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 07:42:30 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/08 07:51:33 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

void		free_fc_struct(t_fc *fc)
{
	ft_strdel(&fc->flags_model);
	ft_strdel(&fc->flags);
	ft_strdel(&fc->str_first);
	ft_strdel(&fc->str_last);
}
