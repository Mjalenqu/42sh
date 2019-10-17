/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 14:32:39 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 09:51:29 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int				check_entry(void)
{
	struct winsize	w;
	char			*s;

	if (!(s = malloc(sizeof(char) * 10000000)))
		exit(0);
	free(s);
	if (ioctl(0, TIOCGWINSZ, &w) == -1)
	{
		ft_printf_err("Entry is not a tty\nExit\n");
		exit(0);
	}
	return (0);
}

int				check_ans(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

char			*make_ans(t_pos *pos, t_hist *hist, t_var *env)
{
	termcaps42sh(pos, hist, env);
	if (pos->ans_heredoc)
		remake_pos_ans(pos);
	pos->ans = check_for_tilde(pos->ans, env, 0, 0);
	pos->last_cmd_on_bg = 0;
	tcsetattr(0, TCSANOW, &pos->old_term);
	return (pos->ans);
}

int				main_loop(t_pos *pos, t_var *my_env, t_hist *hist)
{
	char		*ans;

	ans = make_ans(pos, hist, my_env);
	job_notification(&my_env);
	if (ans == NULL)
		return (1);
	if (check_ans(ans) == 1 && pos->error != 2)
	{
		ft_strdel(&ans);
		return (0);
	}
	if (pos->error == 1)
		error_handling(pos, NULL, 0);
	if ((check_error(ans)) != -1 && pos->error != 2)
		start_exec(start_lex(my_env, ans), my_env);
	else
		pos->ans = ft_secure_free(pos->ans);
	pos->error = 0;
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_hist	*hist;
	t_var	*my_env;
	t_pos	pos;
	pid_t	shell_pid;

	(void)ac;
	if (check_term() == -1)
		exit(0);
	check_entry();
	shell_pid = getpid();
	setpgid(shell_pid, shell_pid);
	tcsetpgrp(STDIN_FILENO, shell_pid);
	my_env = init_env(env, &pos, av, 0);
	shlvl(my_env);
	hist = (t_hist *)malloc(sizeof(t_hist));
	init_t_hist(hist);
	main_init_pos(&pos, my_env);
	hist = create_history(&pos, hist);
	while (1)
	{
		if (main_loop(&pos, stock(NULL, 6), hist) != 0)
			break ;
	}
	free_job_list();
}
