/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key_current_dir.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 10:41:18 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/11 09:52:36 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

static t_htab		*building_htab_current(struct dirent *read, t_htab *htab,
					DIR *dirp)
{
	while ((read = readdir(dirp)) != NULL)
	{
		htab = add_list_back_htab(htab);
		htab->content = ft_strdup(read->d_name);
		htab->content_no = htab->prev == NULL ? 0 : htab->prev->content_no + 1;
		if (htab->prev == NULL)
			htab->lenght_max = ft_strlen(htab->content);
		else
			htab->lenght_max =
			htab->prev->lenght_max < ft_strlen(htab->content) ?
			ft_strlen(htab->content) : htab->prev->lenght_max;
		htab->content_type = (int)read->d_type;
	}
	closedir(dirp);
	return (htab);
}

t_htab				*looking_for_current(t_pos *pos, t_htab *htab, char **path,
					char **name)
{
	DIR				*dirp;
	struct dirent	*read;
	char			*pwd;

	read = NULL;
	pwd = ft_strnew(1000);
	ft_bzero(pwd, 999);
	if ((dirp = opendir(*path)) != NULL)
	{
		ft_strcpy(pwd, *path);
		if (*name == NULL)
			add_slash_on_ans(pos);
	}
	else
	{
		if (*path && *path[0] != 0)
			*name = ft_strjoinf(*path, *name, 2);
		pwd = getcwd(pwd, 1000);
		dirp = opendir(pwd);
	}
	htab = building_htab_current(read, htab, dirp);
	free(pwd);
	htab = adjust_lenght_max(htab);
	return (htab);
}
