/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signal.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:09:42 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/05 11:21:47 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void			signal_handler(void)
{
	ft_printf("\n");
}

static void		ctrl_c(t_pos *pos, t_hist *hist)
{
	t_var		*var;

	var = stock(NULL, 6);
	if (pos->last_cmd_on_bg == 1)
		return ;
	while (hist && hist->next)
		hist = hist->next;
	if (pos->active_heredoc == 1)
	{
		hist->cmd = ft_secure_free(hist->cmd);
		pos->ans_heredoc_save = ft_secure_free(pos->ans_heredoc_save);
		pos->ans_heredoc = ft_secure_free(pos->ans_heredoc);
		free_hdoc(pos->hdoc);
	}
	write(1, "\n", 1);
	hist->cmd = ft_secure_free(hist->cmd);
	pos->ans = ft_secure_free(pos->ans);
	pos->saved_ans = ft_secure_free(pos->saved_ans);
	print_first_prompt(pos);
	pos->ctrl_hist_cmd = ft_secure_free(pos->ctrl_hist_cmd);
	init_pos(pos, 1);
	pos->is_complete = 1;
	add_list_env(&var, SPE, ft_strdup("?"), ft_strdup("1"));
	print_prompt(pos);
}

static void		sighandler(int signum)
{
	t_pos		*pos;

	pos = to_stock(NULL, 1);
	if (signum == RESIZING)
		resize_screen(pos);
	if (signum == CTRL_C)
		ctrl_c(pos, to_stock(NULL, 5));
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
