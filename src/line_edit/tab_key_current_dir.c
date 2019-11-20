/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_key_current_dir.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rlegendr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 10:41:18 by rlegendr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 14:55:30 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "termcaps.h"

void				print_htab_debug(t_htab *htab)
{
	if (!htab)
		ft_printf("htab est nulle\n");
	else
	{
		ft_printf("=======================\n");
		while (htab->prev)
			htab = htab->prev;
		while (htab)
		{
			ft_printf("content = [%s] - ", htab->content);
			ft_printf("content_type = %d - ", htab->content_type);
			ft_printf("content_no = %d - ", htab->content_no);
			ft_printf("lenght_max = %d - ", htab->lenght_max);
			ft_printf("matching_index = %d \n", htab->matching_index);
			htab = htab->next;
		}
		ft_printf("=======================\n");
	}
}

static t_htab		*building_htab_current(struct dirent *read, t_htab *htab,
					DIR *dirp)
{
	while ((read = readdir(dirp)) != NULL)
	{
		htab = add_list_back_htab(htab);
		htab->content = ft_strdup(read->d_name);
		if (ft_strcmp(read->d_name, ".") && ft_strcmp(read->d_name, ".."))
			htab->content_no = htab->prev == NULL ? 0 :
			htab->prev->content_no + 1;
		else
			htab->content_no = htab->prev == NULL ? 0 :
			htab->prev->content_no;
		if (htab->prev == NULL && ft_strcmp(read->d_name, ".") &&
				ft_strcmp(read->d_name, ".."))
			htab->lenght_max = ft_strlen(htab->content);
		else if (ft_strcmp(read->d_name, ".") &&
				ft_strcmp(read->d_name, ".."))
			htab->lenght_max =
				htab->prev->lenght_max < ft_strlen(htab->content) ?
				ft_strlen(htab->content) : htab->prev->lenght_max;
		else
			htab->lenght_max = htab->prev == NULL ? 0 :
				htab->prev->lenght_max;
		htab->content_type = (int)read->d_type;
	}
	closedir(dirp);
	return (htab);
}

static void			moving_name_or_path(char **str)
{
	char			*tmp;

	tmp = *str;
	*str = remove_backslash(*str, 0, 0);
	free(tmp);
}

t_htab				*looking_for_current(t_pos *pos, t_htab *htab, char **path,
					char **name)
{
	DIR				*dirp;
	char			*pwd;

	if (*name == NULL)
		moving_name_or_path(path);
	else
		moving_name_or_path(name);
	if ((dirp = opendir(*path)) != NULL)
	{
		pwd = ft_strnew(1000);
		ft_strcpy(pwd, *path);
		if (*name == NULL)
			add_slash_on_ans(pos);
	}
	else
	{
		if (*path && *path[0] != 0)
			*name = ft_strjoinf(*path, *name, 2);
		pwd = getcwd(NULL, 1000);
		dirp = opendir(pwd);
	}
	if (dirp)
		htab = building_htab_current(NULL, htab, dirp);
	free(pwd);
	return (adjust_lenght_max(htab));
}
