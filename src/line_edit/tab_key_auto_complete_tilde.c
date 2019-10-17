/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key_auto_complete_tilde.c                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 07:35:37 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 11:09:17 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int				get_length_of_home_env(t_var *env)
{
	while (env != NULL && (ft_strcmp("HOME", env->name)))
		env = env->next;
	if (env == NULL && env->data == NULL)
		return (0);
	return (ft_strlen(env->data));
}

void			reduce_ans_for_tilde(t_pos *pos, char *name)
{
	int			search_i;
	int			len;

	len = get_length_of_home_env(stock(NULL, 6)) - 1;
	pos->len_ans += len;
	while (len > 0)
	{
		right_arrow(pos);
		len--;
	}
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
