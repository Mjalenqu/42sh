/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env_i_flag_tool.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:56:08 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 15:00:04 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void			fill_new_link_in_env(t_var *new_env, char **new_env_var)
{
	new_env->name = new_env_var[0];
	new_env->data = new_env_var[1];
	new_env->type = ENVIRONEMENT;
}

void			print_new_env(t_var **new_env, t_var **head)
{
	*new_env = *head;
	print_env(*new_env);
}
