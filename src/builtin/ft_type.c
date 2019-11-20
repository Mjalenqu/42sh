/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_type.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/20 14:14:27 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 15:45:00 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/exec.h"

int				is_builtin(char *function)
{
	int i;

	i = -1;
	while (++i < LEN_BUILTIN_LIST)
	{
		if (ft_strcmp(function, g_builtin_list[i].name) == 0)
		{
			ft_printf_fd("%s is a shell builtin\n", function);
			return (1);
		}
	}
	return (0);
}

int				is_alias(char *function, t_var *var)
{
	while (var)
	{
		if (ft_strcmp(function, var->name) == 0 && var->type == 2)
		{
			ft_printf_fd("%s is an alias of %s\n", function, var->data);
			return (1);
		}
		var = var->next;
	}
	return (0);
}

char			is_function(char *function, t_var **var)
{
	char	*path_env;
	char	**path;
	char	*path_function;
	int		i;

	if ((path_env = ft_get_val("PATH", *var, ENVIRONEMENT)) != NULL)
	{
		i = -1;
		path = ft_strsplit(path_env, ':');
		while (path[++i])
		{
			path_function = ft_strjoin(ft_strjoin(path[i], "/"), function);
			if (ft_file_xrights(path_function))
			{
				ft_printf_fd("%s is %s\n", function, path_function);
				return (1);
			}
		}
	}
	if (ft_file_xrights(function))
	{
		ft_printf_fd("%s is %s\n", function, function);
		return (1);
	}
	return (0);
}

int				ft_type(t_process *p, t_var **var)
{
	int i;
	int ret;

	i = 0;
	ret = 1;
	while (p->cmd[++i])
	{
		if (is_alias(p->cmd[i], *var))
			ret = 0;
		else if (is_builtin(p->cmd[i]))
			ret = 0;
		else if (is_function(p->cmd[i], var))
			ret = 0;
		else
			ft_printf_err_fd("%s not found\n", p->cmd[i]);
	}
	return (ret);
}
