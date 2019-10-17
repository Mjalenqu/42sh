/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection_tools.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/18 18:15:37 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/18 18:16:03 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void			free_ar_lexeur(t_lexeur ***array)
{
	int		i;

	i = 0;
	while ((*array)[i])
	{
		ft_strdel(&(*array)[i]->word);
		ft_strdel(&(*array)[i]->redirection);
		i++;
	}
	free((*array));
}
