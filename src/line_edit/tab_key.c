/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/10 09:39:47 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 16:10:52 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

static int		is_on_token(char *ans, int i)
{
	if (ft_strncmp(ans + i, "&&", 2) == 0 || ft_strncmp(ans + i, "||", 2) == 0)
		return (2);
	else if (ans[i] == '&' || ans[i] == '|' || ans[i] == ';')
		return (1);
	return (0);
}

static int		is_on_var(t_pos *pos)
{
	int		i;

	i = pos->let_nb - 1;
	while (i >= 0 && pos->ans[i] != 32 && is_on_token(pos->ans, i) == 0)
	{
		if (pos->ans[i] == '$' && odd_backslash(i - 1, pos->ans) == 0)
			return (1);
		i -= 1;
	}
	return (0);
}

int				scan_ans(t_pos *pos, int i, int *passed_exe, int *ret)
{
	while (i < pos->let_nb && pos->ans[i] == 32)
	{
		i++;
		if (i == pos->let_nb || pos->ans[i] != 32)
			return (i);
	}
	if (*passed_exe != 2 && pos->ans[i] != 32)
		return (scan_ans_current_file(passed_exe, ret, i, pos));
	else if ((*ret = is_on_token(pos->ans, i)))
	{
		i += *ret;
		*ret = -1;
		*passed_exe = 0;
		return (i);
	}
	else
		*ret = 1;
	return (i);
}

int				get_usage(t_pos *pos)
{
	int		i;
	int		passed_exe;
	int		ret;

	i = 0;
	passed_exe = 0;
	if (pos->let_nb == 0)
		return (-1);
	if (is_on_var(pos) == 1)
		return (2);
	while (i < pos->let_nb && pos->ans[i] == ' ')
		i += 1;
	if (i == pos->let_nb)
		return (-1);
	if (is_on_token(pos->ans, i))
		return (-1);
	while (i < pos->let_nb && pos->ans[i])
	{
		i = scan_ans(pos, i, &passed_exe, &ret);
		if (i == pos->let_nb || pos->ans[i] == '\0')
			break ;
		i++;
	}
	return (ret);
}

void			input_is_tab(t_pos *pos)
{
	int		usage;
	char	*path;
	char	*name;
	t_htab	*htab;

	htab = NULL;
	pos->ans_printed = 1;
	if ((usage = get_usage(pos)) == -1)
		return ;
	path = get_full_path(pos);
	name = get_correct_path(path);
	if (usage == 0 && path[0] != '.' && path[0] != '/')
		htab = looking_for_all(pos, htab, &name);
	else if (usage == 1 || (usage == 0 && (path[0] == '.' || path[0] == '/')))
		htab = looking_for_current(pos, htab, &path, &name);
	else if (usage == 2)
		htab = looking_for_var(pos, htab, &name);
	if (htab && name == NULL && (usage == 1 || usage == 2 ||
		(usage == 0 && (path[0] == '.' || path[0] == '/'))))
		prepare_to_print_htab(pos, htab);
	else if (htab)
		htab = prepare_auto_complete(pos, htab, name);
	ft_free_void(path, name, NULL, NULL);
	free_htab(htab);
	pos->braceparam = 0;
}
