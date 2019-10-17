/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_conditions.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/01 18:00:20 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 15:53:59 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int		double_quote(char *ans, int i)
{
	while (ans[i])
	{
		if (ans[i] == '"' && ans[i - 1] != 92)
			return (i);
		i++;
	}
	return (-1);
}

int		simple_quote(char *ans, int i)
{
	while (ans[i])
	{
		if (ans[i] == 39)
			return (i);
		i++;
	}
	return (-1);
}

int		brace_param(char *ans, int i)
{
	t_pos		*pos;

	pos = to_stock(NULL, 1);
	while (ans[i])
	{
		if (ans[i] == '}' && ans[i - 1] != 92)
			return (i);
		i++;
	}
	pos->error = 2;
	ft_printf_err("\n42sh : syntax {T.red.B.}error{eoc} for braceparam\n");
	return (ft_strlen(ans));
}

int		double_token(char *ans, int i)
{
	int	j;

	j = i - 1;
	if (i - 2 == 0)
		return (ft_strlen(ans));
	while (ans[i] && (ans[i] == 32 || (ans[i] >= 9 && ans[i] <= 13)))
	{
		if (ans[i] != 92 && (ans[i + 1] == '&' || ans[i + 1] == '|'))
			return (ft_strlen(ans));
		i++;
	}
	if (!ans[i])
		return (-1);
	else
		return (j);
}

int		simple_pipe(char *ans, int i)
{
	int	j;

	j = i;
	if (i - 1 == 0)
		return (ft_strlen(ans));
	if (ans[i] == '\0')
		return (-1);
	while (ans[i] && (ans[i] == 32 || (ans[i] >= 9 && ans[i] <= 13)))
	{
		if (ans[i] != 92 && (ans[i + 1] == '&' || ans[i] == '|'))
			return (ft_strlen(ans));
		i++;
	}
	if (i == j)
		return (ft_strlen(ans));
	else if (!ans[i])
		return (-1);
	else
		return (j);
}
