/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_for_tilde.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 10:19:33 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/03 15:07:46 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

char		*verif_env_home(t_var *env)
{
	while (env != NULL && ft_strcmp("HOME", env->name) != 0)
		env = env->next;
	if (env == NULL || (env && env->data == NULL))
		return (NULL);
	return (env->data);
}

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

char		*check_for_tilde(char *ans, t_var *env, int i, int usage)
{
	char	*tmp;

	if (ft_strchr(ans, '~') == NULL)
		return (ans);
	if ((tmp = verif_env_home(env)) == NULL)
		return (ans);
	if (usage == 1)
	{
		while (i > 0 && ans[i - 1] != 32)
			i--;
		if (ans[i] == '~' && check_valid_tilde(ans, i))
			ans = replace_tilde_by_home(ans, i, tmp);
	}
	else
	{
		while (ans[i])
		{
			if (ans[i] == '~' && check_valid_tilde(ans, i))
				ans = replace_tilde_by_home(ans, i, tmp);
			i++;
		}
	}
	return (ans);
}
