/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   replace.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 17:27:56 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 13:00:29 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"
#include "../../includes/termcaps.h"

char		*env_var(t_var *env, char *str)
{
	t_var	*start;

	start = env;
	while (start)
	{
		if (ft_strcmp(start->name, str) == 0 && start->type == ENVIRONEMENT)
		{
			ft_strdel(&str);
			return (start->data);
		}
		start = start->next;
	}
	ft_strdel(&str);
	return (ft_strdup(""));
}

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

int			remove_env_while(char ***array, t_var *var)
{
	int		done;
	int		i;

	done = 0;
	i = 0;
	while ((*array)[i])
	{
		if ((*array)[i][0] == '$')
		{
			done = 1;
			(*array)[i] = env_var(var, ft_strsub((*array)[i], 1,
			ft_strlen((*array)[i])));
		}
		if (f_check_var_alias(var, (*array)[i]) == 1)
		{
			done = 1;
			(*array)[i] = check_var_alias(var, (*array)[i]);
		}
		i++;
	}
	return (done);
}

char		*remove_env(t_var *start, char *str)
{
	char	**array;
	char	*tmp;

	array = ft_strsplit(str, ' '); // TODO FAIRE UN VRAI SPLIT AVEC \T ETC.
	while (1) // TODO faire en sorte qu'on ne peut pas faire de boucle infinie comme bash on ne peut pas replace 2 fois une var.
		if (remove_env_while(&array, start) == 0)
			break ;
	ft_strdel(&str);
	tmp = make_string(array);
	return (tmp);
}
