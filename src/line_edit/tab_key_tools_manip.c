/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key_tools_manip.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 10:46:14 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/02 08:54:37 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

t_htab			*adjust_lenght_max(t_htab *htab)
{
	while (htab)
	{
		htab->lenght_max = htab->next == NULL ?
			htab->lenght_max : htab->next->lenght_max;
		if (htab->prev == NULL)
			break ;
		htab = htab->prev;
	}
	return (htab);
}

char			*get_full_path(t_pos *pos)
{
	int			i;
	int			len;
	char		*search;

	search = NULL;
	i = pos->let_nb;
	if (i == 0)
		return (NULL);
	while (i > 0 && pos->ans[i - 1] != ' ')
		i -= 1;
	len = i;
	while (pos->ans[len] && pos->ans[len] != ' ')
		len += 1;
	search = ft_strndup(pos->ans + i, len - i);
	search = check_for_tilde(search, stock(NULL, 6), 0, 0);
	return (search);
}

char			*get_correct_path(char *path)
{
	int			i;
	char		*name;
	DIR			*test;

	name = NULL;
	if ((test = opendir(path)) != NULL)
	{
		closedir(test);
		return (name);
	}
	i = ft_strlen(path) - 1;
	if (i == -1)
		return (NULL);
	while (i >= 0 && path[i] != '/')
		i -= 1;
	if (i < 0)
		return (NULL);
	name = ft_strdup(path + i + 1);
	path[i + 1] = '\0';
	return (name);
}

void			reduce_ans(t_pos *pos, char *name)
{
	int			search_i;

	while (pos->ans[pos->let_nb] && pos->ans[pos->let_nb] != 32 &&
			pos->ans[pos->let_nb] != '&' && pos->ans[pos->let_nb] != '|' &&
			pos->ans[pos->let_nb] != ';')
		right_arrow(pos);
	search_i = ft_strlen(name) - 1;
	while (search_i >= 0 && pos->let_nb + 1 >= 0 &&
		is_the_same_letter_unsensitive(name[search_i],
		pos->ans[pos->let_nb - 1]))
	{
		input_is_backspace(pos);
		search_i -= 1;
	}
}

void			add_slash_on_ans(t_pos *pos)
{
	int			i;

	i = ft_strlen(pos->ans) - 1;
	if (i == -1)
		return ;
	if (pos->ans[0] == '.' && pos->ans[1] == 0)
	{
		pos->let_nb = 1;
		input_is_printable_char(pos, "/");
		return ;
	}
	while (pos->ans[pos->let_nb] && pos->ans[pos->let_nb] != ' ')
		pos->let_nb += 1;
	if (pos->ans[pos->let_nb - 1] != '/' &&
		!(pos->ans[pos->let_nb - 1] == '.' &&
		(pos->ans[pos->let_nb - 2] == '/' ||
		pos->ans[pos->let_nb - 2] == ' ')))
		input_is_printable_char(pos, "/");
}
