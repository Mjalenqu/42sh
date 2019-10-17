/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_alias.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/29 09:16:52 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 12:56:57 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void	write_alias(t_var *var, t_pos *p)
{
	chdir(p->path);
	if ((p->alias = (open("./.aliases", O_WRONLY
		| O_TRUNC | O_CREAT, 0664))) != -1)
		while (var)
		{
			if (var->type == 2)
			{
				write(p->alias, var->name, ft_strlen(var->name));
				write(p->alias, "=", 1);
				write(p->alias, var->data, ft_strlen(var->data));
				write(p->alias, "\n", 1);
			}
			var = var->next;
		}
}

t_var	*fill_alias(t_var *var, char *line)
{
	var->next = malloc(sizeof(t_var));
	var = var->next;
	var->name = init_name(line);
	var->data = init_data(line);
	var->type = ALIAS;
	var->next = NULL;
	return (var);
}

void	init_alias(t_var *var, t_pos *pos, char *line)
{
	char	*pwd;
	int		ret;

	pos->path = getcwd(NULL, 255);
	pwd = ft_strjoin(pos->path, "/.aliases");
	if ((pos->alias = open(pwd, O_RDWR | O_APPEND | O_CREAT, 0666)) == -1)
	{
		ft_strdel(&pwd);
		return ;
	}
	ft_strdel(&pwd);
	while (var->next)
		var = var->next;
	while ((ret = get_next_line(pos->alias, &line)) > 0)
	{
		if (ft_strlen(line) > 0)
		{
			transform_tab_into_space(line);
			var = fill_alias(var, line);
		}
		if (line != NULL)
			ft_strdel(&line);
	}
	close(pos->alias);
}
