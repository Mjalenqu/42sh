/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_for_tilde.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 10:19:33 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 15:22:07 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

int			check_valid_tilde(char *ans, int i)
{
	if (i == 0)
		return (1);
	if (i > 0)
	{
		if (ans[i - 1] == 32)
			return (1);
	}
	return (0);
}

char		*replace_tilde_by_home(char *ans, int i, char *home)
{
	char	*new_ans;

	new_ans = ft_copy_part_str(ans, i - 1, 0);
	new_ans = ft_strjoinf(new_ans, home, 1);
	new_ans = ft_strjoinf(new_ans, ans + i + 1, 1);
	free(ans);
	return (new_ans);
}

int			verif_tilde(char *ans, int i)
{
	if ((i == 0 || (i > 0 && odd_backslash(i, ans) == 0 &&
		(ans[i - 1] == 32 || ans[i - 1] == 92))) &&
		(ans[i + 1] == '/' || ans[i + 1] == 32 || ans[i + 1] == 0))
	{
		return (1);
	}
	return (0);
}

int			search_for_valid_tilde(char *ans)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (ans[i])
	{
		while (ans[i] && ans[i] != '~')
			i++;
		if (ans[i] == '~')
		{
			if (verif_tilde(ans, i))
				check = 1;
			i++;
		}
	}
	return (check);
}

char		*check_for_tilde(char *ans, t_var *env, int i, int usage)
{
	char	*tmp;

	if (search_for_valid_tilde(ans) == 0)
		return (ans);
	while (env != NULL && ft_strcmp("HOME", env->name) != 0)
		env = env->next;
	if (env == NULL || (env && env->data == NULL))
		return (ans);
	tmp = env->data;
	if (usage == 1)
	{
		while (i > 0 && ans[i - 1] != 32)
			i--;
		if (ans[i] == '~' && check_valid_tilde(ans, i))
			ans = replace_tilde_by_home(ans, i, tmp);
	}
	else
	{
		while (ans[++i])
		{
			if (ans[i] == '~' && check_valid_tilde(ans, i))
				ans = replace_tilde_by_home(ans, i, tmp);
		}
	}
	return (ans);
}
