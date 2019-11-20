/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token_conditions.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/01 18:00:20 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 13:00:45 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int		add_space(t_pos *pos, int *i)
{
	char	*swap;

	swap = NULL;
	if (*i <= 0)
		return (1);
	swap = ft_strnew(*i + 1);
	swap = ft_strncpy(swap, pos->ans, *i);
	swap = ft_strjoinf(swap, " ", 1);
	swap = ft_strjoinf(swap, pos->ans + *i, 1);
	free(pos->ans);
	pos->ans = swap;
	*i = *i + 1;
	return (1);
}

int		is_my_index_open(t_pos *pos, int i, char open, int limit)
{
	while (pos->ans[i] && i != limit)
	{
		if (open != -1 && (pos->ans[i] == open ||
					(open == '$' && pos->ans[i] == '}')) &&
				(odd_backslash(i - 1, pos->ans) == 0 || pos->ans[i] == 39))
			open = -1;
		else if (open == -1 &&
				(pos->ans[i] == '"' || pos->ans[i] == 39 ||
				(pos->ans[i] == '$' && pos->ans[i + 1] == '{')) &&
				(i == 0 || (i > 0 && odd_backslash(i - 1, pos->ans) == 0)))
			open = pos->ans[i];
		i++;
	}
	if (pos->ans[i] == '\0' && i != limit)
		return (0);
	if (open == -1)
		return (1);
	return (0);
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

int		only_space_after_index(char *ans, int i)
{
	while (ans[i] && (ans[i] == 32 || (ans[i] >= 9 && ans[i] <= 13)))
		i++;
	if (ans[i] == '\0')
		return (1);
	return (0);
}

int		simple_pipe(char *ans, int i)
{
	int	j;
	int	check;

	check = i - 2;
	j = i;
	if (i - 1 == 0)
		return (ft_strlen(ans));
	if (i == ft_strlen(ans) || only_space_after_index(ans, i))
	{
		while (check > -1 && ans[check] != '\n' && (ans[check] == 32 ||
					(ans[check] >= 9 && ans[check] <= 13)))
			check--;
		if (check == -1 || ans[check] == '\n')
			return (ft_strlen(ans));
		else
			return (-1);
	}
	while (ans[i] && (ans[i] == 32 || (ans[i] >= 9 && ans[i] <= 13)))
		i++;
	if (ans[i] == '\0')
		return (-1);
	if (i == j)
		return (i + 1);
	else
		return (j);
}
