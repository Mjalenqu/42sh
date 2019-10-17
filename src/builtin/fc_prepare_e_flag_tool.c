/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_prepare_e_flag_tool.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:32:11 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 15:46:45 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

char			*check_new_cmd_is_valid(char *new_cmds, char **paths)
{
	int				i;
	DIR				*dirp;
	struct dirent	*read;

	i = 0;
	while (paths[i])
	{
		paths[i] = free_strjoin(paths[i], "/");
		dirp = opendir(paths[i]);
		while ((read = readdir(dirp)) != NULL)
		{
			if (ft_strcmp(new_cmds, read->d_name) == 0)
			{
				new_cmds = ft_secure_free(new_cmds);
				new_cmds = ft_strdup(read->d_name);
				new_cmds = ft_strjoinf(paths[i], new_cmds, 2);
				return (new_cmds);
			}
		}
		closedir(dirp);
		i++;
	}
	ft_printf_err("42sh: command not found: %s\n", new_cmds);
	return (0);
}
