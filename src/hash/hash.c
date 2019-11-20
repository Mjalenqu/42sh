/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/09 13:32:51 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 14:25:14 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/hash.h"

static char			*complete_hash_table(t_hash *tmp, char *arg, char *path)
{
	while (tmp->next != NULL && tmp->exec != NULL && ft_strcmp(arg, tmp->exec)
			!= 0)
		tmp = tmp->next;
	if (tmp->exec != NULL && ft_strcmp(arg, tmp->exec) == 0)
		tmp->hit += 1;
	else
		init_single_link(tmp, arg, path);
	return (ft_strdup(tmp->path));
}

void				read_hash_table(t_hash **hash)
{
	int				i;
	t_hash			*tmp;

	i = 0;
	while (i < NB_KEY)
	{
		tmp = hash[i];
		while (tmp != NULL)
		{
			if (tmp->path != NULL && tmp->hit >= 1)
				ft_printf_fd("%s used by %s %d time(s)\n",
						tmp->path, tmp->exec, tmp->hit);
			tmp = tmp->next;
		}
		i++;
	}
}

static char			*search_exec_in_table(t_hash *hash, char *arg)
{
	while (hash)
	{
		if (hash != NULL && hash->exec != NULL &&
				ft_strcmp(hash->exec, arg) == 0)
		{
			hash->hit += 1;
			return (ft_strdup(hash->path));
		}
		hash = hash->next;
	}
	return (NULL);
}

char				*fill_hash_table(char *path, char *arg)
{
	t_hash			**hash;
	int				key;
	char			*ans;

	ans = NULL;
	hash = NULL;
	hash = stock_hash(hash, 1);
	key = get_key_of_exec(arg);
	if (hash == NULL)
	{
		hash = (t_hash**)ft_malloc(sizeof(t_hash*) * 100);
		init_hash_links(hash);
		stock_hash(hash, 0);
	}
	else
		ans = search_exec_in_table(hash[key], arg);
	if (ans != NULL)
		return (ans);
	ans = complete_hash_table(hash[key], arg, path);
	return (ans);
}

char				*check_path_hash(t_var **var, char *arg,
		int i, char *ans)
{
	char			**paths;
	t_hash			**hash;
	int				denied;
	char			**env;

	if (search_exec_in_tmp_path(var, arg, &ans) != -1)
		return (ans);
	if ((denied = 0) == 0 && ft_strchr(arg, '/') != 0)
		return (absolute_path(arg, ft_strdup(arg)));
	if ((hash = stock_hash(NULL, 1)) != NULL &&
	(ans = search_exec_in_table(hash[get_key_of_exec(arg)], arg)) != NULL)
	{
		if (access(ans, F_OK) == -1 || access(ans, X_OK) == -1)
			ans = remove_old_entry_in_hash(hash, ans, arg, var);
		ft_strdel(&arg);
		return (ans);
	}
	env = split_env(*var);
	paths = get_ide_paths(env, 1, NULL);
	ft_free_tab(env);
	denied = test_all_paths_existence(paths, arg, &i);
	if (denied > 0)
		return (path_found(paths, i, ans, arg));
	else
		return (path_denied(paths, arg, denied));
}
