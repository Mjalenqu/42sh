/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_tool.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/04 11:05:11 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 14:32:15 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/check_error.h"

void	error_heredoc_go_next(char *str, int *i)
{
	char	*tag;
	char	*tmp;
	int		s;

	tag = get_tag(str, i);
	(*i) += g_fill_token[7].size;
	while (str[*i])
	{
		jump_space(str, i);
		s = *i;
		while (str[*i] && ((str[*i] < 9 || str[*i] > 13) && str[*i] != ' '))
			(*i)++;
		tmp = ft_strsub(str, s, *i - s);
		if (!ft_strcmp(tmp, tag))
		{
			ft_strdel(&tmp);
			ft_strdel(&tag);
			return ;
		}
		ft_strdel(&tmp);
		(*i)++;
	}
	if (tmp)
		ft_strdel(&tmp);
	ft_strdel(&tag);
}

int		first_check(char *str, int i, int token)
{
	int		j;

	j = 0;
	jump_space(str, &j);
	if (j == i)
		return (syntax_print_error(token));
	return (0);
}

int		second_check(char *str, int i, int token)
{
	i += g_fill_token[token].size;
	jump_space(str, &i);
	if (!str[i])
		return (syntax_print_error(token));
	return (0);
}

void	moove_next_quote(char c, char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
}
