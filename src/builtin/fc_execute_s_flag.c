/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_execute_s_flag.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/24 13:41:03 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/11 13:45:20 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

static void		exec_s_flag(t_fc *fc, t_hist *hist, t_var **var)
{
	char	*cmd;
	char	*tmp_cmd;

	*var = stock(NULL, 6);
	tmp_cmd = ft_strdup(hist->cmd);
	if (fc->ename != NULL)
		tmp_cmd = replace_cmd_content_with_ename(fc, tmp_cmd);
	cmd = ft_strdup(tmp_cmd);
	ft_printf_fd("%s\n", tmp_cmd);
	if (token(tmp_cmd, to_stock(NULL, 1)) && valid_heredocs(tmp_cmd, 0, -1) &&
		(check_error(hist->cmd)) != -1 && ft_strstr(tmp_cmd, "fc ") == NULL)
		start_exec(start_lex(*var, tmp_cmd), *var);
	else
	{
		ft_printf_err_fd("42sh: fc: bad command\n");
		ft_free_void(tmp_cmd, NULL, NULL, NULL);
	}
	place_new_cmds_in_history(cmd, hist);
}

static void		correct_int_first(t_fc *fc, t_hist *hist)
{
	if (fc->str_first && ((fc->str_first[0] >= '0' &&
		fc->str_first[0] < '9') || (fc->str_first[0] == '-' &&
		fc->str_first[1] >= '0' && fc->str_first[1] < '9')))
		fc->int_first = ft_atoi(fc->str_first);
	if (fc->int_first < 0)
		fc->int_first = hist->cmd_no + fc->int_first;
	if (fc->int_first < 0)
	{
		fc->error = 1;
		ft_printf_err_fd("%s: fc: history specification out of range\n", TERM);
	}
	if (fc->int_first >= hist->cmd_no || fc->int_first == 0)
		fc->int_first = hist->cmd_no - 1;
}

static void		finish_s_flag(t_fc *fc, t_hist *hist, t_var **var)
{
	while (hist->prev && hist->cmd_no + 1 > fc->int_first)
		hist = hist->prev;
	if (fc->int_first == 0 && hist->next->cmd == NULL)
	{
		fc->error = 1;
		ft_printf_err_fd("%s: fc: history specification out of range\n", TERM);
	}
	if (fc->error == 0)
		exec_s_flag(fc, hist, var);
	else
	{
		remove_cmd_from_hist(hist);
		overwrite_history_file(hist);
	}
}

void			prepare_s_flag(t_fc *fc, t_hist *hist, t_var **var)
{
	if (fc->first_is_str == 0 || fc->str_first == NULL ||
	((fc->str_first[0] == '-' && fc->str_first[1] >= '0' && fc->str_first[1]
	< '9') || (fc->str_first[0] >= '0' && fc->str_first[0] < '9')))
		correct_int_first(fc, hist);
	else if (fc->first_is_str == 1)
	{
		if (fc->str_first[0] == '-' && (fc->str_first[1] < '0' ||
			fc->str_first[1] > '9'))
			fc->int_first = -1;
		fc->first_is_str = 1;
		make_str_arg_into_int(fc, hist);
	}
	if (fc->error == 1)
		return ;
	finish_s_flag(fc, hist, var);
}
