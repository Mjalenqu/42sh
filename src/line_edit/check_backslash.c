/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_backslash.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 14:32:39 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 10:49:13 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void		replace_last_hist(t_hist *hist, char *ans)
{
	while (hist->next)
		hist = hist->next;
	hist = hist->prev;
	free(hist->cmd);
	hist->cmd = ft_strdup(ans);
}

char		*check_backslash_heredoc(t_pos *pos, t_hist *hist)
{
	int		i;
	int		j;
	char	*new_ans;

	i = 0;
	j = 0;
	if (pos->ans[0] == '\0' || ft_strchr(pos->ans, 92) == NULL)
		return (pos->ans);
	new_ans = ft_strnew(ft_strlen(pos->ans));
	while (pos->ans && pos->ans[i] != '\0')
	{
		if (pos->ans[i] == 92 && pos->ans[i + 1] == '\n')
			i++;
		else
			new_ans[j++] = pos->ans[i];
		i++;
	}
	new_ans[j] = '\0';
	pos->ans = ft_secure_free(pos->ans);
	replace_last_hist(hist, new_ans);
	return (new_ans);
}

int			odd_backslash(int i, char *ans)
{
	int		count;

	count = 0;
	while (i >= 0 && ans[i] == 92)
	{
		count += 1;
		i--;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}

int			count_valid_backslash(int i, char *ans)
{
	int		count;

	count = 0;
	while (i >= 0 && ans[i] == 92)
	{
		count += 1;
		i--;
	}
	if (count % 2 == 0)
		return (count / 2);
	return ((count - 1) / 2);
}

char		*check_backslash(t_pos *pos, int i, int j, int count)
{
	char	*new_ans;

	if (pos->ans[0] == '\0' || ft_strchr(pos->ans, 92) == NULL)
		return (pos->ans);
	new_ans = ft_strnew(ft_strlen(pos->ans));
	while (pos->ans && pos->ans[i] != '\0')
	{
		if ((pos->ans[i] == 39 && odd_backslash(i, pos->ans) == 0 &&
		is_my_index_open(pos, 0, -1, i)) ||
		(count % 2 == 1 && pos->ans[i] == 39))
			count++;
		if (pos->ans[i] == 92 && pos->ans[i + 1] == '\n' && odd_backslash(i,
				pos->ans) && count % 2 == 0)
			i++;
		else
			new_ans[j++] = pos->ans[i];
		i++;
	}
	new_ans[j] = '\0';
	pos->ans = ft_secure_free(pos->ans);
	return (new_ans);
}
