/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key_auto_complete.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 11:21:44 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 12:58:57 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

int			wildcard_match(char *s1, char *s2)
{
	if (*s1 && *s2 == '*')
		return (wildcard_match(s1, s2 + 1) || wildcard_match(s1 + 1, s2));
	else if ((*s1 == '\0') && *s2 == '*')
		return (wildcard_match(s1, (s2 + 1)));
	else if (*s1 && *s2 && is_the_same_letter_unsensitive(*s1, *s2))
		return (wildcard_match((s1 + 1), (s2 + 1)));
	else if ((*s1 == '\0') && (*s2 == '\0'))
		return (1);
	return (0);
}

t_htab		*get_current_match(t_htab *htab, char *name, int wildcard)
{
	t_htab	*new;
	int		match;

	new = NULL;
	while (htab)
	{
		match = ft_strstr_case_unsensitive(htab->content, name);
		if ((wildcard == 0 && match != -1) ||
			(wildcard == 1 && wildcard_match(htab->content, name)))
		{
			new = fill_new_htab(htab, new, match);
			if (new->prev == NULL)
				new->lenght_max = ft_strlen(new->content);
			else
				new->lenght_max = new->lenght_max > new->prev->lenght_max ?
					ft_strlen(new->content) : new->prev->lenght_max;
		}
		if (htab->next == NULL)
			break ;
		htab = htab->next;
	}
	if (new == NULL)
		return (htab);
	free_htab(htab);
	return (new);
}

t_htab		*get_intelligent_match(t_htab *htab, char *name)
{
	t_htab	*new;

	new = NULL;
	while (htab->prev)
		htab = htab->prev;
	while (htab)
	{
		if ((ft_strncmp_case_unsensitive(htab->content,
			name, ft_strlen(name))) == 0)
		{
			new = fill_new_htab(htab, new, 0);
			if (new->prev == NULL)
				new->lenght_max = ft_strlen(new->content);
			else
				new->lenght_max = new->lenght_max > new->prev->lenght_max ?
					ft_strlen(new->content) : new->prev->lenght_max;
		}
		if (htab->next == NULL)
			break ;
		htab = htab->next;
	}
	if (new == NULL)
		return (htab);
	free_htab(htab);
	return (new);
}

void		auto_complete(t_pos *pos, t_htab *htab, char *name,
			char *old_pos_ans)
{
	pos->ans = check_for_tilde(pos->ans, stock(NULL, 6), pos->let_nb, 1);
	if (ft_strcmp(old_pos_ans, pos->ans) == 0)
		reduce_ans(pos, name);
	else
		reduce_ans_for_tilde(pos, name);
	input_is_a_string_of_printable_char(pos, htab->content);
	while (pos->ans[pos->let_nb] && pos->ans[pos->let_nb] != 32 &&
			pos->ans[pos->let_nb] != '&' && pos->ans[pos->let_nb] != '|' &&
			pos->ans[pos->let_nb] != ';')
		pos->let_nb += 1;
	if (is_a_directory(pos->ans, pos))
		add_slash_on_ans(pos);
	else if (pos->ans[pos->let_nb] == 32)
		right_arrow(pos);
	else if (pos->braceparam != 1)
		input_is_printable_char(pos, " ");
	clean_at_start(pos);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), 0, pos->start_li), 1, ft_putchar);
	print_prompt(pos);
	print_ans(pos, 0, pos->start_co);
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), pos->act_co, pos->act_li), 1, ft_putchar);
	free(old_pos_ans);
}

t_htab		*prepare_auto_complete(t_pos *pos, t_htab *htab, char *name)
{
	int		wildcard;
	int		i;

	wildcard = 0;
	i = 0;
	while (name[i])
	{
		if (name[i] == '*')
			wildcard = 1;
		i += 1;
	}
	htab = get_current_match(htab, name, wildcard);
	if (wildcard == 0)
		htab = get_intelligent_match(htab, name);
	adjust_lenght_max(htab);
	if (htab->content_no == 0)
		auto_complete(pos, htab, name, ft_strdup(pos->ans));
	else
		prepare_to_print_htab(pos, htab);
	return (htab);
}
