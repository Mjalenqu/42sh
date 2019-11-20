/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_d_flag.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/10 13:44:09 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 15:45:26 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void		delete_first_link(t_hash **hash, t_hash *tmp, int key)
{
	t_hash	*save;

	ft_printf_fd("hash: entry %s deleted from hash table\n", tmp->exec);
	save = tmp->next;
	ft_secure_free(tmp->exec);
	ft_secure_free(tmp->path);
	ft_secure_free(tmp);
	hash[key] = save;
}

void		delete_middle_link(t_hash *tmp)
{
	t_hash	*to_link;

	ft_printf_fd("hash: entry %s deleted from hash table\n", tmp->next->exec);
	to_link = tmp->next->next;
	ft_secure_free(tmp->next->exec);
	ft_secure_free(tmp->next->path);
	ft_secure_free(tmp->next);
	tmp->next = to_link;
}

int			check_if_table_is_empty(t_hash **hash)
{
	int		i;
	t_hash	*tmp;
	int		check;

	check = 1;
	i = 0;
	while (i < NB_KEY)
	{
		tmp = hash[i];
		if (tmp != NULL && tmp->path != NULL)
		{
			check = 0;
			break ;
		}
		i++;
	}
	return (check);
}

void		entry_found_in_hash_table(t_hash *tmp, char *cmd, t_hash **hash,
			int key)
{
	if (tmp->exec != NULL && ft_strcmp(tmp->exec, cmd) == 0)
		delete_first_link(hash, tmp, key);
	else
	{
		while (tmp->next != NULL)
		{
			if (tmp->next->exec != NULL &&
				ft_strcmp(tmp->next->exec, cmd) == 0)
				delete_middle_link(tmp);
			tmp = tmp->next;
		}
	}
}

int			remove_selected_entry_hash(t_hash **hash, char **cmd)
{
	int		key;
	int		i;
	t_hash	*tmp;
	int		ret;

	ret = 0;
	i = 1;
	if (!cmd || !cmd[i] || !cmd[i + 1])
		return (1);
	while (cmd[++i])
	{
		key = get_key_of_exec(cmd[i]);
		tmp = hash[key];
		if (tmp != NULL && tmp->path != NULL)
			entry_found_in_hash_table(tmp, cmd[i], hash, key);
		else if (cmd[i])
		{
			ft_printf_err_fd("hash: %s: entry not found in hash table\n",
					cmd[i]);
			ret = 1;
		}
	}
	return (ret);
}
