/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_spe_params.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/02 18:07:45 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 08:20:27 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

char		*get_spe_param_data(char c, char **av)
{
	if (c == '0')
		return (ft_strdup(av[0]));
	else if (c == '?')
		return (ft_strdup("0"));
	else if (c == '$')
		return (ft_itoa(getpid()));
	else if (c == '!')
		return (ft_strdup("0"));
	else if (c == '_')
		return (ft_strdup(""));
	return (NULL);
}

t_var		*init_spe_params(char **av)
{
	char	*spe;
	int		i;
	t_var	*save;
	t_var	*env;

	i = 0;
	save = malloc(sizeof(t_var));
	env = save;
	spe = ft_strdup("0?$!_");
	while (spe[i])
	{
		save->name = ft_strnew(1);
		save->name[0] = spe[i];
		save->next = NULL;
		save->data = get_spe_param_data(spe[i], av);
		save->type = 4;
		i++;
		if (spe[i])
		{
			save->next = malloc(sizeof(t_var));
			save = save->next;
		}
	}
	ft_strdel(&spe);
	return (env);
}
