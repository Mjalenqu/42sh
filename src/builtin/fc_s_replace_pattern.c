/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_s_replace_pattern.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/06 10:54:44 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/10 13:56:22 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

char		*fill_new_cmd(char *tmp_cmd, char *model, char *replace)
{
	char	*new_tmp;
	int		i;
	char	*tmp;

	i = 0;
	new_tmp = ft_strnew(0);
	while (tmp_cmd[i])
	{
		if (tmp_cmd[i] == model[0] && ft_strncmp(tmp_cmd + i, model,
					ft_strlen(model)) == 0)
		{
			new_tmp = ft_strjoinf(new_tmp, replace, 1);
			i += ft_strlen(model);
		}
		else
		{
			tmp = ft_strndup(tmp_cmd + i, 1);
			new_tmp = ft_strjoinf(new_tmp, tmp, 3);
			i++;
		}
	}
	return (new_tmp);
}

char		*replace_cmd_content_with_ename(t_fc *fc, char *tmp_cmd)
{
	char	*model;
	char	*replace;
	int		i;
	int		j;
	char	*new_tmp;

	j = 0;
	i = 0;
	while (fc->ename[i] != '=')
		i++;
	model = ft_strnew(i + 1);
	i = 0;
	while (fc->ename[i] != '=')
	{
		model[i] = fc->ename[i];
		i++;
	}
	model[i] = '\0';
	replace = ft_strnew(ft_strlen(fc->ename) - i++);
	while (fc->ename[i])
		replace[j++] = fc->ename[i++];
	new_tmp = fill_new_cmd(tmp_cmd, model, replace);
	return (new_tmp);
}
