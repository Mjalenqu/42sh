/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history_expansion_types.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 15:06:24 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/04 14:08:48 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int				double_exclamation_expansion(char **new_ans, t_hist *hist)
{
	if (!hist->prev || !hist->prev->cmd)
		return (-1);
	*new_ans = ft_strjoinf(*new_ans, hist->prev->cmd, 1);
	return (0);
}

int				number_expansion(char **new_ans, t_hist *hist, char *expansion)
{
	int			nb;

	if (ft_strlen(expansion + 1) > 9)
		return (-1);
	nb = ft_atoi(expansion + 1);
	if (!hist->prev)
		return (-1);
	while (hist->prev)
		hist = hist->prev;
	while (hist->next && --nb > 0)
		hist = hist->next;
	if (nb > 0)
		return (-1);
	*new_ans = ft_strjoinf(*new_ans, hist->cmd, 1);
	return (0);
}

int				negative_number_expansion(char **new_ans, t_hist *hist,
				char *expansion)
{
	int			nb;

	if (ft_strlen(expansion + 1) > 9)
		return (-1);
	nb = ft_atoi(expansion + 1);
	while (hist && hist->prev && nb++ < 0)
		hist = hist->prev;
	if (nb < 0)
		return (-1);
	*new_ans = ft_strjoinf(*new_ans, hist->cmd, 1);
	return (0);
}

int				word_finding_expansion(char **new_ans, t_hist *hist,
				char *expansion, t_pos *pos)
{
	if (!hist->prev)
		return (-1);
	hist = hist->prev;
	while (hist && hist->prev &&
		ft_strncmp(expansion + 1, hist->cmd, ft_strlen(expansion + 1)) != 0)
		hist = hist->prev;
	if (ft_strcmp(pos->ans, hist->cmd) == 0 || ft_strncmp(expansion + 1,
				hist->cmd, ft_strlen(expansion + 1)) != 0)
		return (-1);
	*new_ans = ft_strjoinf(*new_ans, hist->cmd, 1);
	return (0);
}

int				get_expansion_value(char *expansion, t_hist *hist,
				char **new_ans, t_pos *pos)
{
	if (expansion[1] == '!')
		return (double_exclamation_expansion(new_ans, hist));
	else if (expansion[1] >= 48 && expansion[1] <= 57)
		return (number_expansion(new_ans, hist, expansion));
	else if (expansion[1] == '-' && expansion[2] && expansion[2] >= 47 &&
			expansion[2] <= 57)
		return (negative_number_expansion(new_ans, hist, expansion));
	else if (expansion[1] && expansion[1] != '!' &&
		(expansion[1] < 9 || expansion[1] > 13) && expansion[1] != 32)
		return (word_finding_expansion(new_ans, hist, expansion, pos));
	else
		return (-1);
}
