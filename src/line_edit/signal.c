/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signal.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:09:42 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 09:04:34 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

struct s_hist	**ghist;

void			signal_handler(void)
{
	ft_printf("\n");
}

static void		resize_screen(t_pos *pos)
{
	int			len;

	check_term();
	pos->max_co = tgetnum("co");
	pos->max_li = tgetnum("li") - 1;
	len = get_len_with_lines(pos);
	pos->let_nb = ft_strlen(pos->ans);
	pos->len_ans = pos->let_nb;
	short_update(pos, len);
	clean_at_start(pos);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), 0, pos->start_li), 1, ft_putchar);
	print_prompt(pos);
	if (pos->ctrl_search_history == 1)
	{
		write(1, "(reverse-i-search)'", 19);
		ft_printf("%s':", pos->ans);
		write(1, pos->ctrl_hist_cmd, ft_strlen(pos->ctrl_hist_cmd));
	}
	else
		print_ans(pos, 0, pos->start_co);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
}

static void		ctrl_c(t_pos *pos)
{
	char		*pwd;

	remove_last_link_hist();
	if (pos->last_cmd_on_bg == 1)
		return ;
	while ((*ghist)->next)
		*ghist = (*ghist)->next;
	if (pos->active_heredoc == 1)
	{
		(*ghist)->cmd = ft_secure_free((*ghist)->cmd);
		pos->ans_heredoc_save = ft_secure_free(pos->ans_heredoc_save);
		pos->ans_heredoc = ft_secure_free(pos->ans_heredoc);
		free_hdoc(pos->hdoc);
	}
	write(1, "\n", 1);
	pos->ans = ft_secure_free(pos->ans);
	pos->saved_ans = ft_secure_free(pos->saved_ans);
	ft_printf("\n{B.T.cyan.}42sh {eoc}{B.}--- {B.T.yellow.}%s{eoc}\n",
		pwd = pos->pwd);
	pos->ctrl_hist_cmd = ft_secure_free(pos->ctrl_hist_cmd);
	init_pos(pos, 1);
	pos->is_complete = 1;
	print_prompt(pos);
}

static void		sighandler(int signum)
{
	t_pos		*pos;

	pos = to_stock(NULL, 1);
	if (signum == RESIZING)
		resize_screen(pos);
	if (signum == CTRL_C)
		ctrl_c(pos);
}

void			signal_list(void)
{
	signal(SIGWINCH, sighandler);
	signal(SIGINT, sighandler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGILL, SIG_IGN);
	signal(SIGTRAP, SIG_IGN);
	signal(SIGEMT, SIG_IGN);
	signal(SIGFPE, SIG_IGN);
	signal(SIGSYS, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}
