/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/08 10:53:46 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 17:07:17 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"
#include "../../includes/lexeur.h"

void	shlvl(t_var *env, int ac, char **av)
{
	int	i;

	(void)ac;
	(void)av;
	while (env)
	{
		if (ft_strcmp("SHLVL", env->name) == 0)
		{
			i = ft_atoi(env->data);
			i++;
			ft_strdel(&env->data);
			env->data = ft_itoa(i);
			return ;
		}
		env = env->next;
	}
}

char	*init_data(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	if (src[i])
		i++;
	dest = ft_strsub(src, i, ft_strlen(src) - i);
	return (dest);
}

char	*init_name(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	dest = ft_strsub(src, 0, i);
	return (dest);
}

t_var	*init_env(char **env, t_pos *pos, char **av, int i)
{
	t_var	*new;
	t_var	*save;

	new = init_spe_params(av);
	save = new;
	while (new->next)
		new = new->next;
	new->next = ft_malloc(sizeof(t_var));
	new = new->next;
	while (env[i])
	{
		new->name = init_name(env[i]);
		new->data = init_data(env[i]);
		new->type = ENVIRONEMENT;
		i++;
		if (env[i])
		{
			new->next = (t_var*)ft_malloc(sizeof(t_var));
			new = new->next;
		}
	}
	new->next = NULL;
	init_alias(save, pos, NULL);
	stock(save, 5);
	return (save);
}

void	free_env(t_var *env)
{
	t_var *buf;

	while (env)
	{
		buf = env->next;
		free(env->name);
		free(env->data);
		free(env);
		env = buf;
	}
}
