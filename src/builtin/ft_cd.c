/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/26 13:18:39 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 16:45:49 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int		get_cd_option(char **cmd, int *i, int ret, int j)
{
	while (cmd[++(*i)] && ft_strcmp(cmd[*i], "--") != 0)
	{
		j = 0;
		if (cmd[*i][0] == '-' && cmd[*i][1])
		{
			while (cmd[*i][++j])
			{
				if (cmd[*i][j] == 'L' || cmd[*i][j] == 'P')
					ret = cmd[*i][j];
				else
				{
					ft_printf_err_fd("42sh: cd: %c: invalid option\n",
							cmd[*i][j]);
					return (-1);
				}
			}
		}
		else
			break ;
	}
	if (cmd[*i] && ft_strcmp(cmd[*i], "--") == 0)
		*i += 1;
	return (ret);
}

char	*move_to_new_dir(char *cmd, t_var **var, char *new_path)
{
	int			i;
	char		**tmp;

	i = 0;
	new_path = fill_new_path(&tmp, new_path, cmd, var);
	while (tmp[i])
	{
		if (ft_strcmp(tmp[i], "..") == 0)
			new_path = replace_double_dot_by_real_path(new_path);
		else if (ft_strcmp(tmp[i], ".") != 0)
		{
			new_path = ft_strjoinf(new_path, tmp[i], 1);
			if (verif_path(new_path, 1, 0) == 0)
			{
				ft_free_tab(tmp);
				free(new_path);
				return (NULL);
			}
			new_path = ft_strjoinf(new_path, "/", 1);
		}
		i++;
	}
	ft_free_tab(tmp);
	return (new_path);
}

char	*get_path(char *cmd, t_var **var, char *new_path, int option)
{
	if (cmd == NULL || ft_strcmp(cmd, "--") == 0 || (cmd && cmd[0] == '~' &&
		verif_tilde(cmd, 0) == 1))
		new_path = move_to_home_dir(var);
	else if (ft_strcmp(cmd, "-") == 0)
		new_path = move_to_oldpwd(var);
	else
	{
		if (option == 'P')
		{
			new_path = ft_strdup(cmd);
			new_path = verif_p_option_path(new_path, 0, 0);
		}
		else
			new_path = move_to_new_dir(cmd, var, new_path);
	}
	return (new_path);
}

void	replace_pwd_vars_in_env(t_var **var, char *new_path, int option)
{
	char	*tmp;
	char	*tmp_pwd;

	if (option == 'P')
	{
		tmp = getcwd(NULL, 1000);
		new_path = ft_secure_free(new_path);
	}
	else
		tmp = new_path;
	if (ft_get_val("PWD", *var, ENVIRONEMENT) != NULL)
	{
		tmp_pwd = ft_strdup(ft_get_val("PWD", *var, ENVIRONEMENT));
		add_list_env(var, ENVIRONEMENT, ft_strdup("OLDPWD"), tmp_pwd);
	}
	else
		add_list_env(var, ENVIRONEMENT, ft_strdup("OLDPWD"), ft_strdup(tmp));
	add_list_env(var, ENVIRONEMENT, ft_strdup("PWD"), tmp);
}

int		ft_cd(t_process *p, t_var **var)
{
	int		option;
	int		i;
	char	*new_path;
	t_pos	*pos;
	t_var	*old_env;

	old_env = copy_env(*var);
	pos = to_stock(NULL, 1);
	option = 0;
	new_path = NULL;
	i = 0;
	add_list_env(var, ENVIRONEMENT, ft_strdup("PWD"), ft_strdup(pos->pwd));
	if (check_arguments_number(p, &i, &option, old_env) == 1)
		return (1);
	if ((new_path = get_path(p->cmd[i], var, new_path, option)) == NULL)
	{
		if (p->cmd[1] && ft_get_val("CDPATH", *var, ENVIRONEMENT) != NULL &&
				(new_path == NULL || verif_path(new_path, 1, 0) == 0))
			new_path = verif_path_in_cdpath(new_path, *var, p->cmd, 1);
		else
			new_path = ft_strdup(p->cmd[i]);
	}
	return (finish_ft_cd(new_path, pos, old_env, option));
}
