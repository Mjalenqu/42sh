/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_prepare_e_flag.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/05 14:02:04 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 11:36:00 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

void			correct_int_first_and_int_last_for_e_flag(t_fc *fc,
				t_hist *hist)
{
	if (ft_strlen(fc->flags) == 0 && ft_strlen(fc->ename) > 1 &&
		((fc->ename[0] > '1' && fc->ename[0] < '9') || (fc->ename[0] == '-' &&
		fc->ename[1] > '0' && fc->ename[1] < '9')))
		fc->int_first = ft_atoi(fc->ename);
	if (fc->first_not_precised == 1 && fc->last_not_precised == 1)
	{
		fc->int_first = hist->cmd_no - 1;
		fc->int_last = hist->cmd_no - 1;
	}
	if (fc->int_first > hist->cmd_no)
		fc->int_first = hist->cmd_no - 1;
	if (fc->int_last > hist->cmd_no)
		fc->int_last = hist->cmd_no - 1;
	else if (fc->first_not_precised == 1)
		fc->int_first = hist->cmd_no - 1;
	else if (fc->last_not_precised == 1)
		fc->int_last = fc->int_first;
	if (fc->int_first < 0)
		fc->int_first = (hist->cmd_no + fc->int_first);
	if (fc->int_last < 0)
		fc->int_last = (hist->cmd_no + fc->int_last);
}

static int		check_if_ename_is_text_editor(t_fc *fc, char **paths, int i)
{
	DIR				*dirp;
	struct dirent	*read;

	if (paths == NULL)
		return (-1);
	while (paths[++i])
	{
		paths[i] = free_strjoin(paths[i], "/");
		dirp = opendir(paths[i]);
		while ((read = readdir(dirp)) != NULL)
		{
			if (ft_strcmp(fc->ename, read->d_name) == 0)
			{
				fc->ename = ft_secure_free(fc->ename);
				fc->ename = ft_strdup(read->d_name);
				fc->ename = ft_strjoinf(paths[i], fc->ename, 2);
				closedir(dirp);
				return (1);
			}
		}
		closedir(dirp);
	}
	fc->error = 1;
	ft_printf_err("42sh: command not found: %s\n", fc->ename);
	return (0);
}

char			**get_ide_paths(char **env)
{
	int				i;
	char			**paths;

	i = 0;
	paths = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			paths = ft_strsplit(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (paths);
}

void			prepare_e_flag_free(char **paths, char **env)
{
	ft_free_tab(paths);
	ft_free_tab(env);
}

void			prepare_e_flag(t_fc *fc, t_hist *hist, t_var **var, int i)
{
	char		**env;
	char		**paths;

	env = split_env(*var);
	paths = get_ide_paths(env);
	if (fc->ename == NULL || (fc->ename[0] > '0' && fc->ename[0] < '9'))
	{
		if (fc->ename != NULL)
		{
			fc->int_last = fc->int_first;
			fc->int_first = ft_atoi(fc->ename);
		}
		fc->ename = ft_strdup("/usr/bin/vim");
		send_e_flag_to_exec(fc, hist, env);
	}
	else if (check_if_ename_is_text_editor(fc, paths, i - 1) == 1)
		send_e_flag_to_exec(fc, hist, env);
	prepare_e_flag_free(paths, env);
	if (fc->error == 1)
	{
		hist = hist->prev;
		remove_cmd_from_hist(hist);
		overwrite_history_file(hist);
	}
	fc->ename = ft_secure_free(fc->ename);
}
