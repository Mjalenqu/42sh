/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/10 09:39:47 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 13:01:48 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int				is_on_token(char *ans)
{
	if (ft_strncmp(ans, "&&", 2) == 0 || ft_strncmp(ans, "&", 1) == 0 ||
			ft_strncmp(ans, "||", 2) == 0 || ft_strncmp(ans, "|", 1) == 0 ||
			ft_strncmp(ans, ";", 1) == 0 || ft_strncmp(ans, "`", 1) == 0)
		return (1);
	return (0);
}

static int		is_on_var(t_pos *pos)
{
	int		i;

	i = pos->let_nb - 1;
	while (i >= 0 && pos->ans[i] != 32 && is_on_token(pos->ans + i) == 0)
	{
		if (pos->ans[i] == '$')
			return (1);
		i -= 1;
	}
	return (0);
}

static int		scanning_pos_ans(t_pos *pos, int *i, int *word_number)
{
	if (pos->ans[*i] == ' ')
	{
		while (pos->ans[*i] == ' ' && *i < pos->let_nb)
			*i += 1;
		if (pos->ans[*i] != ' ')
			*word_number += 1;
	}
	else if (is_on_token(pos->ans + *i))
	{
		*word_number = 0;
		*i += 1;
		while (pos->ans[*i] == ' ' && *i < pos->let_nb)
			*i += 1;
		if (*i == pos->let_nb)
			return (-1);
	}
	else
		*i += 1;
	return (0);
}

int				scan_pos_ans(t_pos *pos)
{
	int		i;
	int		word_number;

	i = 0;
	word_number = 0;
	if (pos->let_nb == 0)
		return (-1);
	if (is_on_var(pos) == 1)
		return (2);
	while (pos->ans[i] == ' ')
		i += 1;
	if (i == pos->let_nb)
		return (-1);
	while (pos->ans[i] && i < pos->let_nb)
	{
		if (scanning_pos_ans(pos, &i, &word_number) == -1)
			return (-1);
	}
	if (word_number == 0)
		return (0);
	if (word_number > 0)
		return (1);
	return (1);
}

void			input_is_tab(t_pos *pos)
{
	int		usage;
	char	*path;
	char	*name;
	t_htab	*htab;

	htab = NULL;
	pos->ans_printed = 1;
	if ((usage = scan_pos_ans(pos)) == -1)
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
