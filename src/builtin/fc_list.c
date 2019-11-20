/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_list.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/01 14:33:49 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/01 15:21:04 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

char			**convert_fc_list_to_tab(t_fc_list *fc_list)
{
	int			i;
	int			len;
	char		**ret;
	t_fc_list	*tmp;

	i = 0;
	len = 0;
	tmp = fc_list;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	ret = (char **)ft_malloc(sizeof(char*) * (len + 1));
	while (fc_list)
	{
		tmp = fc_list;
		ret[i] = ft_strdup(fc_list->cmd);
		fc_list = fc_list->next;
		free(tmp->cmd);
		free(tmp);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

t_fc_list		*add_list_back_fc_list(t_fc_list *fc_list, char *line)
{
	t_fc_list	*new;

	new = NULL;
	if (!(new = (t_fc_list*)ft_malloc(sizeof(t_fc_list))))
		return (NULL);
	if (fc_list == NULL)
	{
		new->cmd = ft_strdup(line);
		new->next = NULL;
		return (new);
	}
	while (fc_list->next != NULL)
		fc_list = fc_list->next;
	new->cmd = ft_strdup(line);
	new->next = NULL;
	fc_list->next = new;
	return (new);
}
