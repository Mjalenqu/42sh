/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env_tools.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 10:31:09 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 08:30:58 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

t_var		*fill_var(char *name, char *data, int type)
{
	t_var	*var;

	var = ft_malloc(sizeof(t_var));
	var->name = ft_strdup(name);
	var->data = ft_strdup(data);
	var->type = type;
	var->next = NULL;
	return (var);
}

void		add_list_env(t_var **ptr_var, int type, char *name, char *data)
{
	t_var	*var;
	t_var	*last;

	var = *ptr_var;
	if (!var)
	{
		free_name_and_data(name, data);
		return ;
	}
	while (var != NULL)
	{
		if (ft_strcmp(name, var->name) == 0 && type == var->type)
		{
			ft_strdel(&var->data);
			var->data = ft_strdup(data);
			free_name_and_data(name, data);
			return ;
		}
		if (var->next == NULL)
			last = var;
		var = var->next;
	}
	last->next = fill_var(name, data, type);
	free_name_and_data(name, data);
}

t_var		*put_new_entry_in_var(t_var *var, char **new_env_entry,
		int usage)
{
	if (usage == 0)
		var = add_list_back_env(NULL);
	else if (usage == 1)
	{
		var->next = add_list_back_env(var);
		var = var->next;
	}
	var->name = ft_strdup(new_env_entry[0]);
	var->data = ft_strdup(new_env_entry[1]);
	var->type = ENVIRONEMENT;
	if (usage == 0)
		var->next = NULL;
	return (var);
}

t_var		*init_t_var(t_var *new)
{
	new->data = NULL;
	new->name = NULL;
	new->type = ENVIRONEMENT;
	new->next = NULL;
	return (new);
}

t_var		*add_list_back_env(t_var *env)
{
	t_var	*new;

	new = NULL;
	if (!(new = (t_var*)ft_malloc(sizeof(t_var))))
		return (NULL);
	if (env == NULL)
	{
		init_t_var(new);
		return (new);
	}
	while (env->next != NULL)
		env = env->next;
	init_t_var(new);
	env->next = new;
	return (new);
}
