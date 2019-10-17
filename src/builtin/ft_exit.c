/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_exit.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/27 17:46:07 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 08:31:01 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/exec.h"

static void		write_alias_on_exit(t_var *var)
{
	t_pos *p;

	p = to_stock(NULL, 1);
	chdir(p->path);
	p->alias = open("./.aliases", O_WRONLY | O_TRUNC | O_CREAT, 0664);
	while (var)
	{
		if (var->type == ALIAS)
		{
			write(p->alias, var->name, ft_strlen(var->name));
			write(p->alias, "=", 1);
			write(p->alias, var->data, ft_strlen(var->data));
			write(p->alias, "\n", 1);
		}
		var = var->next;
	}
}

void			free_pos(void)
{
	t_pos *pos;

	pos = to_stock(NULL, 1);
	ft_strdel(&pos->prompt);
	ft_strdel(&pos->path);
	ft_strdel(&pos->ctrl_hist_cmd);
	ft_strdel(&pos->saved_ans);
	ft_strdel(&pos->pwd);
}

void			free_env_list(t_var *var)
{
	t_var	*tmp;

	if (!var)
		return ;
	while (var)
	{
		tmp = var;
		var = var->next;
		free(tmp->name);
		free(tmp->data);
		free(tmp);
	}
}

int				check_if_letter(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int				ft_exit(t_process *p, t_var **var)
{
	int	status;

	status = ft_atoi(p->cmd[1]);
	if (p->cmd && p->cmd[1] && p->cmd[2])
	{
		ft_printf_err("42sh: exit: {B.T.red.}error{eoc}: Too many arguments\n");
		return (1);
	}
	if (p->split == 'P' || p->fd_in != STDIN_FILENO)
		return (status);
	if (status < 0 || (p->cmd[1] && check_if_letter(p->cmd[1]) &&
		(status = 255)))
		ft_printf_err("42sh: exit: %s: numeric argument required\n", p->cmd[1]);
	else
	{
		free_hash_table();
		ft_printf("exit\n");
	}
	write_alias_on_exit(*var);
	free_pos();
	free_t_hist(stock(NULL, 8));
	free_env_list(*var);
	free_job_list();
	exit(status);
}
