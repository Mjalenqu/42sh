/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 08:43:18 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 08:24:13 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_str.h"

char	*get_line(char *str, char **line)
{
	char		*temp;
	int			i;
	int			newl;

	i = 0;
	newl = 0;
	if (!(*str))
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		newl = 1;
	*line = ft_strsub(str, 0, i);
	temp = ft_strsub(str, i + newl, (ft_strlen(str) - (i + newl)));
	str = ft_strcpy(str, temp);
	free(temp);
	return (*line);
}

int		get_next_line(const int fd, char **line)
{
	static char	*str = NULL;
	char		buf[BUFF_SIZE + 1];
	int			ret;

	ret = 1;
	if (fd < 0 || line == NULL || BUFF_SIZE < 1)
		return (-1);
	if (!(str))
		str = ft_strnew(1);
	while (!ft_strchr(str, '\n') && ret > 0)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			str = ft_strjoinf(str, buf, 1);
		}
	}
	buf[ret] = '\0';
	if (ret < 0)
		return (-1);
	if ((*line = get_line(str, line)) == NULL)
		ft_strdel(&str);
	return (*line == NULL ? 0 : 1);
}
