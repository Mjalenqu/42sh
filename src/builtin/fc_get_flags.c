/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_fc_flags.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/08 18:32:18 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/07 07:43:18 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int				find_flags_order(t_fc *fc, char let_a, char let_b, int usage)
{
	int			i;

	i = 0;
	if (usage == 0)
	{
		(void)let_b;
		while (fc->flags[i] && fc->flags[i] != let_a)
			i++;
		return (i);
	}
	return (0);
}

static void		check_flags_errors(t_fc *fc, t_process *p, int i, int j)
{
	if (j < ft_strlen(p->cmd[i]) && ft_strchr(fc->flags, 'e') == NULL)
	{
		ft_printf_err("%s: fc: -%c: invalid option\n", TERM, p->cmd[i][j]);
		print_fc_usage();
		fc->error = 1;
	}
	if ((j < ft_strlen(p->cmd[i]) || !p->cmd[i + 1] || (p->cmd[i + 1] &&
		p->cmd[++i][0] == '-' && p->cmd[i][1] < '0' && p->cmd[i][1] > '9')) &&
		ft_strchr(fc->flags, 'e') != NULL && fc->error++ == 0)
	{
		if (!p->cmd[i + 1] &&
			find_flags_order(fc, 'e', '\0', 0) == ft_strlen(fc->flags) - 1)
		{
			ft_printf_err("%s: fc: -e: option requires an argument\n", TERM);
			print_fc_usage();
		}
		else
		{
			while (j > 0 && p->cmd[i][j - 1] != 'e')
				j--;
			ft_printf_err("%s: fc: %s: command not found\n", TERM,
					p->cmd[i] + j);
		}
	}
}

int				determ_fc_flags(t_fc *fc, t_process *p, int k, int i)
{
	int			j;

	while (p->cmd[i] && ft_strlen(p->cmd[i]) > 1 && p->cmd[i][0] == '-' &&
	p->cmd[i][1] != '-' && (p->cmd[i][1] < '0' || p->cmd[i][1] > '9') &&
	fc->error == 0)
	{
		j = 1;
		while (p->cmd[i][j] && ft_strchr(fc->flags_model, p->cmd[i][j]) != NULL)
		{
			if (ft_strchr(fc->flags, p->cmd[i][j]) == NULL)
				fc->flags[k++] = p->cmd[i][j];
			j++;
		}
		check_flags_errors(fc, p, i++, j);
	}
	fc->flags[k] = '\0';
	if ((((ft_strchr(fc->flags, 'e') != NULL && ft_strchr(fc->flags, 'r') ==
	NULL) || ft_strchr(fc->flags, 's') != NULL) && ft_strlen(fc->flags) > 1) ||
	(ft_strchr(fc->flags, 'e') != NULL && ft_strchr(fc->flags, 'r') != NULL &&
	ft_strlen(fc->flags) > 2))
	{
		print_fc_usage();
		fc->error = 1;
	}
	return (i);
}
