/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/01 18:30:42 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 09:41:57 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int		token_condition(char *ans, int i)
{
	if (ans[i] == '"' && (i == 0 || (i > 0 && ans[i - 1] != 92)))
		i = double_quote(ans, i + 1);
	else if (ans[i] == 39 && (i == 0 || (i > 0 && ans[i - 1] != 92)))
		i = simple_quote(ans, i + 1);
	else if (ans[i] == '$' && ans[i + 1] == '{' && (i == 0 || (i > 0 &&
					ans[i - 1] != 92)))
		i = brace_param(ans, i + 2);
	else if (ans[i] == '&' && ans[i + 1] == '&' && (i == 0 || (i > 0 &&
					ans[i - 1] != 92)))
		i = double_token(ans, i + 2);
	else if (ans[i] == '|' && ans[i + 1] == '|' && (i == 0 || (i > 0 &&
					ans[i - 1] != 92)))
		i = double_token(ans, i + 2);
	else if (ans[i] == '|' && (i == 0 || (i > 0 && ans[i - 1] != 92)))
		i = simple_pipe(ans, i + 1);
	return (i);
}

int		token(char *ans, t_pos *pos)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	if (pos->active_heredoc == 0)
	{
		while (ans[i])
		{
			i = token_condition(ans, i);
			if (i <= -1)
				return (0);
			if (i < ft_strlen(ans))
				i++;
		}
	}
	if (ans && ft_strlen(ans) > 0 && ans[ft_strlen(ans) - 1] == 92 &&
		odd_backslash(ft_strlen(ans) - 1, ans))
		return (0);
	return (1);
}
