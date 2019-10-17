/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_expansion_calculate.c                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 15:11:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 15:13:09 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int				get_expansion_length(char *ans, int i)
{
	int			j;
	int			check;
	int			not_double;
	int			nb_check;

	not_double = 0;
	check = 0;
	j = i;
	nb_check = 0;
	if (ans[j + 1] && ((ans[j + 1] >= '0' && ans[j + 1] <= '9') || (ans[j + 2]
		&& ans[j + 1] == '-' && ans[j + 2] >= '0' && ans[j + 2] <= '9')))
		nb_check = 1;
	while (ans[j] && (ans[j] < 9 || ans[j] > 13) && ans[j] != 32 && check < 2)
	{
		if (ans[j] != '!')
			not_double += 1;
		if (ans[j] == '!' && not_double > 0)
			break ;
		else if (ans[j] == '!')
			check += 1;
		if (j > i + 1 && nb_check == 1 && (ans[j] < '0' || ans[j] > '9'))
			return (j);
		j++;
	}
	return (j);
}

char			*get_expansion_content(char *ans, int i)
{
	char		*new_ans;
	int			j;
	int			k;

	k = 0;
	j = get_expansion_length(ans, i);
	new_ans = ft_strnew(j - i);
	while (i < j)
		new_ans[k++] = ans[i++];
	new_ans[k] = '\0';
	return (new_ans);
}
