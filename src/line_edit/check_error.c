/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:14:23 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void			*ft_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
	{
		ft_printf("42sh: error: memory allocation failed\n");
		ft_printf("42sh: program stops\n");
		exit(126);
	}
	return (ret);
}

int				check_if_process_in_bg(t_pos *pos, unsigned char buf[9])
{
	(void)buf;
	if (pos->last_cmd_on_bg == 1)
		pos->ans = ft_strdup("");
	return (0);
}

int				check_term(void)
{
	int			ret;
	char		*term_type;

	term_type = getenv("TERM");
	ret = 0;
	if (term_type == NULL)
	{
		ft_putstr("TERM must be set (see 'env').\n");
		return (-1);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		ft_putstr("Could not access to the termcap database..\n");
		return (-1);
	}
	else if (ret == 0)
	{
		ft_putcolor("Terminal type", term_type,
			"is not defined in termcap database ");
		ft_putstr("or have too few informations).\n");
		return (-1);
	}
	return (0);
}
