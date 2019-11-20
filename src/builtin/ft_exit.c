/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_exit.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/08 12:06:56 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 15:51:15 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/exec.h"

void			write_alias_on_exit(t_var *var)
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

void			free_pos(t_pos *pos)
{
	ft_strdel(&pos->prompt);
	ft_strdel(&pos->path);
	ft_strdel(&pos->ctrl_hist_cmd);
	ft_strdel(&pos->saved_ans);
	ft_strdel(&pos->pwd);
}

void			kill_last_job(t_job_list *jb, t_pos *pos, t_var *var,
				t_save_job *save)
{
	int		check;

	check = 0;
	while (jb)
	{
		check += 1;
		jb = jb->next;
	}
	if (check)
		ft_printf_fd("There are stopped jobs.\n");
	free_copy_job(save);
	free_job_list(0);
	free_hash_table();
	free_pid_launch();
	ft_printf_fd("exit\n");
	write_alias_on_exit(var);
	free_pos(pos);
	free_t_hist(stock(NULL, 8));
	free_env_list(var);
	tcsetattr(0, TCSANOW, &pos->old_term);
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

int				ft_exit(t_process *p, t_var **var)
{
	t_pos	*pos;
	int		status;
	int		check;
	int		i;

	i = -1;
	check = 0;
	(void)var;
	pos = to_stock(NULL, 1);
	status = ft_atoi(p->cmd[1]);
	if (p->cmd && p->cmd[1] && p->cmd[2])
	{
		ft_printf_err_fd("42sh: exit: error: Too many arguments\n");
		return (1);
	}
	if (p->split == 'P' || p->fd_in != STDIN_FILENO)
		return (1);
	while (p->cmd[1] && p->cmd[1][++i])
		if (p->cmd[1][i] < '0' || p->cmd[1][i] > '9')
			check = 1;
	if ((status < 0 || check) && (status = 255))
		ft_printf_err_fd("42sh: exit: %s: numeric argument required\n",
				p->cmd[1]);
	pos->exit_mode = status;
	return (status);
}
