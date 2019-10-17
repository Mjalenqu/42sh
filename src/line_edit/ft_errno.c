/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_errno.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/24 07:19:15 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 07:21:09 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void			error_adding_list(char *variable, int err, t_hist *err_list)
{
	err_list->cmd = ft_strdup(variable);
	err_list->cmd_no = err;
	err_list = add_list_back_hist(err_list);
}

char			*finding_error_message(char *message, int err_no)
{
	if (err_no == -2)
		message = ft_strdup("event not found");
	return (message);
}

void			error_printing(t_hist *err_list, t_pos *pos)
{
	char	*message;

	(void)pos;
	message = NULL;
	while (err_list->prev != NULL)
		err_list = err_list->prev;
	while (err_list)
	{
		message = finding_error_message(message, err_list->cmd_no);
		if (err_list->cmd != NULL)
			ft_printf_err("42sh: %s: %s\n", err_list->cmd, message);
		if (err_list->next == NULL)
			break ;
		err_list = err_list->next;
	}
}

void			error_handling(t_pos *pos, char *variable, int err)
{
	static t_hist	*err_list;

	if (err_list == NULL)
	{
		err_list = add_list_back_hist(err_list);
		err_list->prev = NULL;
	}
	if (err < 0)
	{
		error_adding_list(variable, err, err_list);
		pos->error = 1;
	}
	else if (err == 0)
	{
		error_printing(err_list, pos);
		free_t_hist(err_list);
		err_list = NULL;
	}
}
