/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env_i_new_env.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 16:12:39 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 16:17:23 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

t_var			*copy_old_env(t_var *old)
{
	t_var *new;

	new = (t_var*)ft_malloc(sizeof(t_var));
	new->data = ft_strdup(old->data);
	new->name = ft_strdup(old->name);
	new->type = old->type;
	new->next = NULL;
	return (new);
}

void			add_list_front_env(t_var *old, t_var **head)
{
	t_var	*to_add;

	if (*head == NULL)
		*head = copy_old_env(old);
	else
	{
		to_add = copy_old_env(old);
		to_add->next = *head;
		*head = to_add;
	}
}

t_var			*add_front_spe_params(t_var *old, t_var *new_env)
{
	while (old)
	{
		if (old->type == SPE)
			add_list_front_env(old, &new_env);
		old = old->next;
	}
	return (new_env);
}

void			print_all_env(t_var *var)
{
	ft_printf("-------------------\n");
	ft_printf("pointeur sur var = %p\n", var);
	if (var)
	{
		while (var)
		{
			ft_printf("var ptr = %p // ", var);
			ft_printf("var name = [%s] // ", var->name);
			ft_printf("var data = [%s] // ", var->data);
			ft_printf("var type = %d\n", var->type);
			var = var->next;
		}
	}
	ft_printf("-------------------\n");
}
