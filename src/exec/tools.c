/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/02 10:55:32 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 11:01:38 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/termcaps.h"

void	split_env_while(t_var **save, int *i)
{
	if ((*save)->type == ENVIRONEMENT)
		(*i)++;
	(*save) = (*save)->next;
}

char	**split_env(t_var *var)
{
	char	**array;
	t_var	*save;
	int		i;
	int		j;

	i = 0;
	save = var;
	while (save)
		split_env_while(&save, &i);
	save = var;
	array = (char**)malloc(sizeof(char*) * (i + 1));
	array[i] = 0;
	j = 0;
	while (save)
	{
		if (save->type == ENVIRONEMENT)
		{
			array[j] = ft_strjoinf(save->name, "=", 0);
			array[j] = ft_strjoinf(array[j], save->data, 1);
			j++;
		}
		save = save->next;
	}
	return (array);
}

char	*strjoin_path(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, "/");
	ft_strjoin_free(&tmp, s2);
	return (tmp);
}

void	cnf_print_error(char *str)
{
	ft_putstr("42sh: \033[1;31merror: \033[0mcommand not found: ");
	ft_putstr(str);
	ft_putstr("\n");
}

void	ft_tabfree(char **res)
{
	int i;

	i = -1;
	while (res[++i])
		ft_strdel(&res[i]);
	free(res);
}
