/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_file.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 09:46:16 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/16 12:43:44 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"

void		fill_process_split(t_job **j, t_lexeur **res, int i)
{
	int		k;

	k = i;
	while (res[k] && (res[k]->word || (res[k]->token == 4 ||
	res[k]->token == 5 || res[k]->token == 6 || res[k]->token == 7)))
	{
		k++;
	}
	if (res[k] && res[k]->token == 0)
		(*j)->p->split = 'A';
	else if (res[k] && res[k]->token == 2)
		(*j)->p->split = '|';
	else if (res[k] && res[k]->token == 3)
		(*j)->p->split = 'P';
	else
		(*j)->p->split = '\0';
}

char		*add_space_content(char *content)
{
	char	*res;
	int		i;

	i = 0;
	if (!content)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(content) + 1));
	while (content[i])
	{
		if (content[i] == -1)
			res[i] = ' ';
		else
			res[i] = content[i];
		i++;
	}
	res[i] = '\0';
	ft_strdel(&content);
	return (res);
}

char		*get_content(char *tag, t_lexeur **res, int *t, int *size)
{
	char	*content;

	(*t)++;
	content = NULL;
	while (res[*t] && ft_strcmp(res[*t]->word, tag))
	{
		(*size)++;
		if (!content)
			content = ft_strdup(res[*t]->word);
		else
			ft_strjoin_free(&content, res[*t]->word);
		if (res[*t + 1] && ft_strcmp(res[*t + 1]->word, tag))
			ft_strjoin_free(&content, "\n");
		(*t)++;
	}
	(*t)++;
	content = add_space_content(content);
	return (content);
}

void		make_tmp_great_again(t_redirect **tmp)
{
	(*tmp)->next = malloc(sizeof(t_redirect));
	*tmp = (*tmp)->next;
	(*tmp)->heredoc_content = NULL;
}

void		add_heredoc(char *tag, t_lexeur **res, int *i)
{
	(*i)++;
	while (res[*i] && !ft_strcmp(res[*i]->word, tag))
		(*i)++;
	(*i)++;
}
