/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 11:06:30 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 08:24:59 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/builtin.h"
#include "../../includes/termcaps.h"

const t_builtin	g_builtin_list[LEN_BUILTIN_LIST] =
{
	{"test", &ft_test, 1},
	{"alias", &main_alias, 1},
	{"unalias", &main_unalias, 1},
	{"set", &ft_set, 0},
	{"echo", &ft_echo, 0},
	{"cd", &ft_cd, 1},
	{"type", &ft_type, 0},
	{"export", &ft_export, 1},
	{"unset", &ft_unset, 1},
	{"fc", &ft_fc, 1},
	{"fg", &ft_fg, 1},
	{"jobs", &ft_jobs, 1},
	{"exit", &ft_exit, 1},
	{"hash", &ft_hash, 1},
	{"setenv", &ft_setenv, 1},
	{"unsetenv", &ft_unsetenv, 1},
	{"env", &ft_env, 0},
	{"bg", &ft_bg, 1}
};

int		is_builtin_modify(t_process *p)
{
	int i;

	i = -1;
	if (!p->cmd)
		return (0);
	if (!p->cmd[0])
		return (0);
	while (++i < LEN_BUILTIN_LIST)
	{
		if (ft_strcmp(p->cmd[0], g_builtin_list[i].name) == 0)
		{
			if (g_builtin_list[i].modify_data == 1)
				return (1);
			return (0);
		}
	}
	return (0);
}

int		find_builtins(t_process *p, t_var **var)
{
	int i;

	i = -1;
	if (!p->cmd[0])
		return (0);
	while (++i < LEN_BUILTIN_LIST)
	{
		if (ft_strcmp(p->cmd[0], g_builtin_list[i].name) == 0)
		{
			p->ret = g_builtin_list[i].ptr_builtin(p, var);
			add_list_env(var, SPE, ft_strdup("?"), ft_itoa(p->ret));
			return (1);
		}
	}
	return (0);
}

int		test_builtin(t_process *p)
{
	int i;
	int j;

	i = -1;
	j = 0;
	if (!p->cmd[0])
		return (0);
	while (++i < LEN_BUILTIN_LIST)
	{
		while (p->cmd[j] && find_equal(p->cmd[j]) == 1)
			j++;
		if (p->cmd[j] && ft_strcmp(p->cmd[j], g_builtin_list[i].name) == 0)
			return (1);
	}
	return (0);
}
