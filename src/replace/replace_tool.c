/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   replace_tool.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 20:22:43 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 08:18:55 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

char		*make_string(char **array)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (array[i])
	{
		ft_strjoin_free(&res, array[i]);
		if (array[i + 1])
			ft_strjoin_free(&res, " ");
		i++;
	}
	return (res);
}

int			check_backslash_var(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (i == 0 || str[i - 1] != '\\')
	{
		if (i == 0 && !str[i + 1])
			return (0);
		return (1);
	}
	if (!str[i + 1] || (str[i + 1] && str[i + 1] == ' '))
		return (1);
	return (0);
}

int			check_alias(char *array, t_var *var)
{
	t_var		*tmp_var;

	(void)var;
	tmp_var = stock(NULL, 6);
	while (tmp_var && ((ft_strcmp(array, tmp_var->name) != 0)
	|| tmp_var->type != ALIAS))
	{
		tmp_var = tmp_var->next;
	}
	if (!tmp_var)
		return (0);
	return (1);
}
