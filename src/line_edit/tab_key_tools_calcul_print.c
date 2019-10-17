/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key_tools_calcul.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 10:44:21 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 13:36:12 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int				is_a_directory(char *path, t_pos *pos)
{
	DIR			*dirp;
	int			i;
	char		*to_open;
	int			word_index;

	word_index = get_word_index(pos);
	i = word_index;
	while (i - 1 >= 0 && path[i - 1] != 32)
		i -= 1;
	to_open = malloc(word_index - i + 2);
	to_open[word_index - i + 1] = '\0';
	ft_strncpy(to_open, path + i, word_index - i + 1);
	if ((dirp = opendir(to_open)) == NULL)
	{
		free(to_open);
		return (0);
	}
	free(to_open);
	closedir(dirp);
	return (1);
}

int				get_word_index(t_pos *pos)
{
	int			i;

	if (pos->let_nb == ft_strlen(pos->ans))
		return (pos->let_nb - 1);
	i = pos->let_nb;
	if (pos->ans[i] == 32)
		i -= 1;
	while (pos->ans[i + 1] != 32 && pos->ans[i + 1])
		i += 1;
	return (i);
}

void			complete_with_space(t_htab *htab)
{
	int			i;

	i = ft_strlen(htab->content);
	while (i++ < htab->lenght_max)
		write(1, " ", 1);
}

void			print_htab(t_htab *htab, int max_word)
{
	write(1, "\n", 1);
	while (htab->prev)
		htab = htab->prev;
	while (htab)
	{
		if (htab->content_type == 4)
			ft_printf("{B.T.cyan.}%s{eoc}/{eoc}   ", htab == NULL ?
				NULL : htab->content);
		else
			ft_printf("%s    ", htab == NULL ? NULL : htab->content);
		complete_with_space(htab);
		if ((htab->content_no + 1) % max_word == 0 && htab->next != NULL)
			write(1, "\n", 1);
		htab = htab->next;
	}
	write(1, "\n", 1);
}

void			prepare_to_print_htab(t_pos *pos, t_htab *htab)
{
	int			len;
	int			max_word;

	if ((max_word = pos->max_co / (htab->lenght_max + 4)) == 0)
		return ;
	print_htab(htab, max_word);
	get_cursor_info(pos, &pos->start_li, &pos->start_co, 0);
	print_prompt(pos);
	write(1, pos->ans, ft_strlen(pos->ans));
	len = get_len_with_lines(pos);
	pos->act_li = pos->start_li + len / pos->max_co;
	pos->act_co = len % pos->max_co;
	while (pos->act_li > pos->max_li)
	{
		pos->act_li -= 1;
		pos->start_li -= 1;
	}
	len = go_to_let_nb(pos);
	pos->act_li = pos->start_li + len / pos->max_co;
	pos->act_co = len % pos->max_co;
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
}
