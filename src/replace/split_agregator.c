/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   split_agregator.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/04 12:01:45 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/04 12:03:11 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

int		search_agregator(char *str, int i)
{
	int		token;

	while (str[i] && ((str[i] < 9 || str[i] > 13) && str[i] != ' '))
	{
		token = find_token(str, i);
		if (token == 5 || token == 8)
			return (1);
		i++;
	}
	return (0);
}

void	split_agregator(char *str, int *i)
{
	while (str[*i] && (find_token(str, *i) != 5 && find_token(str, *i) != 8))
		(*i)++;
	(*i) += 2;
	if (str[*i] && ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' '))
	{
		while (str[*i] && ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' '))
			(*i)++;
	}
	while (str[*i] && ((str[*i] < 9 || str[*i] > 13) && str[*i] != ' '
	&& (find_token(str, *i) == -1)))
		(*i)++;
}
