/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/09 13:31:38 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 14:25:25 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "termcaps.h"
# include "builtin.h"
# define NB_KEY 100

typedef struct s_var	t_var;

typedef struct		s_hash
{
	char			*path;
	char			*exec;
	int				hit;
	struct s_hash	*next;
}					t_hash;

/*
**	HASH_C fichier check_path_hash dans termcaps.h
*/

char				*fill_hash_table(char *path, char *arg);
void				read_hash_table(t_hash **hash);

/*
**	HASH_TOOLS_C
*/

void				init_single_link(t_hash *hash, char *arg, char *path);
void				free_hash_table(void);
void				init_hash_links(t_hash **hash);
t_hash				**stock_hash(t_hash **to_stock, int usage);
unsigned short		get_key_of_exec(char *str);

/*
**	HASH_PATH_C
*/

int					test_all_paths_existence(char **paths, char *arg, int *i);
char				*absolute_path(char *path, char *tmp);
char				*path_found(char **paths, int i, char *ans, char *arg);
char				*path_denied(char **paths, char *arg, int denied);
int					scan_name_for_undesired_symbols(char *str);

/*
**	HASH_PREPARE_ERROR_C
*/

int					search_exec_in_tmp_path(t_var **var, char *arg, char **ans);
char				*remove_old_entry_in_hash(t_hash **ghash, char *ans,
					char *arg, t_var **var);
void				prepare_error_message_for_hash(int error, char *str);

#endif
