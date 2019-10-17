/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 14:49:17 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 14:37:10 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"
#include "lexeur.h"
#include "exec.h"

void		add_env(t_var **var, char *str, char *name)
{
	t_var	*prev;

	name = init_name(str);
	if (add_env_check(name, var, str) == 1)
		return ;
	while (*var)
	{
		if (ft_strcmp(name, (*var)->name) == 0 && (*var)->type != SPE)
			break ;
		prev = (*var);
		(*var) = (*var)->next;
	}
	if (!(*var))
	{
		(*var) = add_one(str, name);
		prev->next = (*var);
		return ;
	}
	ft_strdel(&(*var)->data);
	ft_strdel(&name);
	(*var)->data = init_data(str);
}

void		remoove_all_quote(char **str)
{
	char **al;

	al = malloc(sizeof(char *) * 3);
	al[2] = 0;
	al[0] = init_name(*str);
	al[1] = init_data(*str);
	remoove_quote(&al);
	ft_strdel(&(*str));
	(*str) = ft_strjoin(al[0], "=");
	ft_strjoin_free(str, al[1]);
	ft_free_tab(al);
}

int			check_utils(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$') != NULL)
			return (0);
		i++;
	}
	return (1);
}

int			local_or_env(t_var **var, char **cmd, int i, char ***tmp)
{
	if (cmd[i] && find_equal(cmd[i]))
	{
		remoove_all_quote(&cmd[i]);
		if (check_cmd(cmd) == 1)
		{
			add_env_temp(var, cmd[i], TEMP);
			*tmp = remove_tab(cmd, i);
		}
		else
		{
			while (cmd[i])
			{
				add_env(var, cmd[i], NULL);
				i++;
			}
			ft_free_tab(cmd);
			return (-1);
		}
	}
	return (0);
}

char		**check_exec_var(char **cmd, t_var **var)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	while (cmd[i])
	{
		if (local_or_env(var, cmd, i, &tmp) == -1)
			return (NULL);
		i++;
	}
	if (tmp != NULL)
	{
		ft_free_tab(cmd);
		return (tmp);
	}
	return (cmd);
}
