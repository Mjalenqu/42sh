/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launch_process.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/29 18:55:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 15:34:54 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

int			ft_execute_function(char *path, char **arg, t_var *var)
{
	char		**tab_var;

	tab_var = split_env(var);
	if (execve(path, arg, tab_var) == -1)
	{
		ft_tabfree(tab_var);
		return (-1);
	}
	return (0);
}

void		update_pid(t_process *p, t_job *j, pid_t pid, t_var **var)
{
	p->pid = pid;
	remember_pid(pid);
	if (j->pgid == 0)
		j->pgid = pid;
	setpgid(pid, j->pgid);
	p->ret = 0;
	if (p->split != 'P' && j->split != '&')
	{
		tcsetpgrp(0, j->pgid);
		wait_process_pid(p->pid, var);
		signal(SIGTTOU, SIG_IGN);
		tcsetpgrp(0, getpid());
		signal(SIGTTOU, SIG_DFL);
		if (p->fd_in != 0)
		{
			update_status(var);
			close(p->fd_in);
		}
	}
}

int			launch_process(t_process *p, t_var *var, char *path)
{
	int	ret;

	ret = 0;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, &signal_handler);
	signal(SIGCHLD, SIG_IGN);
	if (test_builtin(p) != 1)
		get_all_redirections_done(p, to_stock(NULL, 1), p->redirect,
				test_builtin(p));
	if (p->exec_builtin == 0)
		exit(1);
	if (find_builtins(p, &var) != 0)
		exit(p->ret);
	if (path == NULL)
	{
		if (p->hash_error)
			ft_printf_err_fd("%s", p->hash_error);
		exit(127);
	}
	ft_execute_function(path, p->cmd, var);
	exit(127);
	return (0);
}

int			check_path_before_fork(t_process *p, t_var **var, t_job *j,
			char **cmd_path)
{
	t_pos	*pos;

	if (test_builtin(p) == 1)
		get_all_redirections_done(p, to_stock(NULL, 1),
				p->redirect, test_builtin(p));
	to_stock(p, 2);
	pos = to_stock(NULL, 1);
	p->background = j->split == '&' ? 1 : 0;
	if (j->split != '&' && is_builtin_modify(p))
	{
		if (find_builtins(p, var) != 0)
			return (1);
	}
	if (test_builtin(p) != 1 && p && p->cmd && p->cmd[0])
		*cmd_path = check_path_hash(var, ft_strdup(p->cmd[0]), 0, NULL);
	return (0);
}

int			fork_simple(t_job *j, t_process *p, t_var **var, char *cmd_path)
{
	pid_t		pid;
	int			ret;

	*var = stock(NULL, 6);
	if ((ret = check_path_before_fork(p, var, j, &cmd_path)) != 0)
		return (ret);
	pid = fork();
	if (pid < 0)
	{
		ft_strdel(&cmd_path);
		return (-1);
	}
	if (pid == 0)
	{
		launch_process(p, *var, cmd_path);
		ft_strdel(&cmd_path);
	}
	else
	{
		update_pid(p, j, pid, var);
		ft_strdel(&cmd_path);
	}
	ft_strdel(&p->hash_error);
	return (1);
}
