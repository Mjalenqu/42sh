/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   oldget_next_line.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/20 16:06:09 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char	**multi_fd(int fd, t_stock **list)
{
	t_stock		*n_list;
	t_stock		*tmp;

	if (*list)
	{
		tmp = *list;
		while (tmp->next && tmp->fd != fd)
			tmp = tmp->next;
		if (tmp->fd == fd)
			return (&tmp->str);
	}
	if (!(n_list = (t_stock*)ft_malloc(sizeof(t_stock))))
		return (NULL);
	n_list->fd = fd;
	n_list->str = NULL;
	n_list->next = NULL;
	if (*list)
		tmp->next = n_list;
	else
		*list = n_list;
	return (&n_list->str);
}

char	*ft_malloc_str(char *str, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	*line = ft_strsub(str, 0, i);
	if (str[i] == '\n')
	{
		tmp = str;
		str = ft_strsub(str, i + 1, ft_strlen(str) - i - 1);
		ft_strdel(&tmp);
	}
	else
		ft_strdel(&str);
	if (i == 0 && !str)
		return (NULL);
	return (str);
}

char	*ft_concat(char *buff, int ret, char *str)
{
	char	*tmp;

	buff[ret] = '\0';
	tmp = str;
	str = ft_strjoin(str, buff);
	ft_strdel(&tmp);
	return (str);
}

int		get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	int				ret;
	static t_stock	*list = NULL;
	char			**str;

	str = multi_fd(fd, &list);
	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (*str == NULL)
	{
		*str = ft_strdup("\0");
	}
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		*str = (ft_concat(buff, ret, *str));
		if (ft_strstr(*str, "\n") != NULL)
			break ;
	}
	*str = ft_malloc_str(*str, line);
	if (*str == NULL && ft_strcmp(*line, "\0") == 0)
		return (0);
	return (1);
}
