/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_hash.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/10 11:18:33 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int			print_part_of_hash_table(t_hash **hash, char **cmd, int ret)
{
	int		key;
	int		i;
	t_hash	*tmp;

	i = 1;
	while (cmd[i])
	{
		key = get_key_of_exec(cmd[i]);
		tmp = hash[key];
		if (tmp != NULL && tmp->path != NULL)
		{
			while (tmp != NULL)
			{
				if (tmp->path != NULL && ft_strcmp(tmp->exec, cmd[i]) == 0)
					ft_printf_fd("%s used by %s %d time(s)\n",
						tmp->path, tmp->exec, tmp->hit);
				tmp = tmp->next;
			}
		}
		else if (cmd[i] && ret++ == 0)
			ft_printf_err_fd("42sh: hash: %s: not found\n", cmd[i]);
		i++;
	}
	return (ret);
}

void		print_path_hash(t_hash **hash, char **cmd)
{
	int		key;
	int		i;
	t_hash	*tmp;

	i = 1;
	while (cmd[i])
	{
		key = get_key_of_exec(cmd[i]);
		tmp = hash[key];
		if (tmp != NULL)
		{
			while (tmp != NULL)
			{
				if (tmp->path != NULL && ft_strcmp(tmp->exec, cmd[i]) == 0)
					ft_printf_fd("%s is located in path = %s\n",
							cmd[i], tmp->path);
				tmp = tmp->next;
			}
		}
		i++;
	}
}

int			exec_hash_with_flag(t_hash **hash, char flag, char **cmd,
			t_var **var)
{
	int		ret;

	ret = 0;
	(void)var;
	if (flag == 'r')
	{
		free_hash_table();
		ft_printf_fd("hash: hash table cleared\n");
		stock_hash(NULL, 0);
	}
	else if (flag == 't')
		print_path_hash(hash, cmd);
	else if (flag == 'd')
		ret = remove_selected_entry_hash(hash, cmd);
	else
	{
		ft_printf_err_fd("42sh: hash: bad parameter\n");
		return (1);
	}
	return (ret);
}

int			ft_hash(t_process *p, t_var **var)
{
	t_hash	**hash;
	char	*flags;
	int		ret;

	ret = 0;
	flags = "tdr";
	hash = stock_hash(NULL, 1);
	if (hash == NULL || check_if_table_is_empty(hash) == 1)
	{
		ft_printf_err_fd("42sh: hash: hash table not set\n");
		return (1);
	}
	if (!p->cmd[1])
		read_hash_table(hash);
	else if (p->cmd[1][0] == '-' && ft_strlen(p->cmd[1]) == 2 &&
			ft_strchr(flags, p->cmd[1][1]) != NULL)
		ret = exec_hash_with_flag(hash, p->cmd[1][1], p->cmd, var);
	else if (p->cmd[1] && p->cmd[1][0] != '-')
		ret = print_part_of_hash_table(hash, p->cmd, 0);
	else
	{
		ft_printf_err_fd("hash: usage: hash [-rdt] [name]\n");
		return (1);
	}
	return (ret);
}
