/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_tools.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/10 10:37:50 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/04 14:45:58 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/hash.h"

unsigned short		get_key_of_exec(char *str)
{
	int				i;
	unsigned short	sum;

	sum = 0;
	i = 0;
	while (str[i])
	{
		sum += str[i] * (3 + i);
		i++;
	}
	return (sum % NB_KEY);
}

t_hash				**stock_hash(t_hash **to_stock, int usage)
{
	static t_hash	**stock_t_hash = NULL;

	if (usage == 0)
		stock_t_hash = to_stock;
	else if (usage == 1)
		return (stock_t_hash);
	return (NULL);
}

void				free_hash_table(void)
{
	t_hash			**hash;
	t_hash			*to_free;
	t_hash			*tmp;
	int				key;

	key = 0;
	hash = stock_hash(NULL, 1);
	if (hash == NULL)
		return ;
	while (key < NB_KEY)
	{
		to_free = hash[key];
		while (to_free)
		{
			tmp = to_free->next;
			ft_secure_free(to_free->path);
			ft_secure_free(to_free->exec);
			ft_secure_free(to_free);
			to_free = tmp;
		}
		key++;
	}
	free(hash);
}

void				init_hash_links(t_hash **hash)
{
	int				key;

	key = 0;
	while (key < NB_KEY)
	{
		hash[key] = (t_hash*)ft_malloc(sizeof(t_hash));
		hash[key]->path = NULL;
		hash[key]->exec = NULL;
		hash[key]->hit = 0;
		hash[key]->next = NULL;
		key++;
	}
}

void				init_single_link(t_hash *hash, char *arg, char *path)
{
	t_hash			*tmp;

	hash->path = ft_strdup(path);
	hash->exec = ft_strdup(arg);
	hash->hit = 1;
	tmp = (t_hash*)ft_malloc(sizeof(t_hash));
	tmp->path = NULL;
	tmp->exec = NULL;
	tmp->hit = 0;
	tmp->next = NULL;
	hash->next = tmp;
}
