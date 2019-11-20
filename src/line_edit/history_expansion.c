/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_expansion.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/22 07:05:34 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/14 09:29:39 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int				check_if_inside_symbols(char *ans, int i)
{
	int			j;
	int			check_single;

	check_single = 0;
	j = 0;
	while (ans && ans[j] && j < i)
	{
		if (ans[j] == 39)
			check_single += 1;
		j++;
	}
	if ((check_single % 2) == 1)
		return (-1);
	return (0);
}

int				replace_expansion_by_value(t_pos *pos, t_hist *hist, int i,
				int error)
{
	char		*expansion;
	char		*new_ans;

	expansion = get_expansion_content(pos->ans, i);
	new_ans = ft_copy_part_str(pos->ans, i - 1, 0);
	error = get_expansion_value(expansion, hist, &new_ans, pos);
	if (error == -1)
	{
		new_ans = ft_secure_free(new_ans);
		expansion = ft_secure_free(expansion);
		return (error);
	}
	new_ans = ft_strjoinf(new_ans, pos->ans + i + ft_strlen(expansion), 1);
	pos->ans = ft_secure_free(pos->ans);
	pos->ans = ft_strdup(new_ans);
	new_ans = ft_secure_free(new_ans);
	expansion = ft_secure_free(expansion);
	return (error);
}

int				print_new_ans_after_expansion_replace(t_pos *pos, int error)
{
	if (error != -1)
	{
		pos->let_nb = ft_strlen(pos->ans);
		pos->len_ans = pos->let_nb;
		short_update(pos, get_len_with_lines(pos));
		clean_at_start(pos);
		print_ans(pos, 0, 0);
		return (1);
	}
	return (0);
}

int				check_history_expansion(t_pos *pos, t_hist *hist, int i,
				int error)
{
	char		*original_ans;

	if (ft_strchr(pos->ans, '!') == NULL || pos->active_heredoc == 1)
		return (0);
	original_ans = ft_strdup(pos->ans);
	while (pos->ans && pos->ans[++i])
	{
		while (hist && hist->next)
			hist = hist->next;
		if (pos->ans[i] == '!' && (pos->ans[i + 1] != '\0' && pos->ans[i + 1] !=
	'=') && pos->ans[i + 1] != 32 && (i == 0 || (i > 0 && pos->ans[i - 1] != '!'
		&& pos->ans[i - 1] != 92)) && check_if_inside_symbols(pos->ans, i) == 0)
			error = replace_expansion_by_value(pos, hist, i, error);
		if (error == -1)
		{
			ft_printf_err("\n42sh: %s: event not found", original_ans);
			pos->error = 2;
			pos->ans = ft_secure_free(pos->ans);
			pos->ans = ft_strnew(0);
			break ;
		}
	}
	free(original_ans);
	return (print_new_ans_after_expansion_replace(pos, error));
}
