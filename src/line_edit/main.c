/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/04 15:45:25 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/17 09:58:45 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/shell.h"
#include "../../includes/lexeur.h"

void	print_history(t_all *all)
{
	t_history *save;

	save = all->last;
	while (save->prev)
	{
		printf("/ %s /\n", save->cmd);
		save = save->prev;
	}
	printf("/ %s /\n", save->cmd);
}

t_all	*init_all(t_all *all, char **env)
{
	all = malloc(sizeof(t_all));
	get_history(&all->history);
	while (all->history && all->history->next)
		all->history = all->history->next;
	all->select = NULL;
	all->select = init_term(all);
	all->env = init_env(env);
	all->wind = init_wind();
	all->last = all->history;
	all->prompt = ft_strdup("prompt->");
	all->save = NULL;
	return (all);
}

void	end_of_shell(t_all *all)
{
	tcsetattr(2, TCSANOW, &(all->select->old_term));
	tputs(tgetstr("ve", NULL), 1, ft_put_c);
	write_history(all);
	free(all->select);
	free_all(all);
}

void	add_res(char *res, t_all *all)
{
	while (all->last->next != NULL)
		all->last = all->last->next;
	if (all->last->next == NULL)
	{
		all->last->next = malloc(sizeof(t_history));
		all->last->next->prev = all->last;
		all->last = all->last->next;
		all->last->cmd = ft_strdup(res);
		all->last->next = NULL;
	}
	all->history = all->last;
}

int		main(int ac, char **av, char **env)
{
	t_all		*all;

	(void)ac;
	(void)av;
	all = NULL;
	all = init_all(all, env);
	if (check_term() == -1)
		return (0);
	while (1)
	{
		all->save = ft_strdup("");
		while (all->last->next)
			all->last = all->last->next;
		all->history = all->last;
		tputs(tgetstr("ve", NULL), 1, ft_put_c);
		key_hook(all);
		ft_putcolor("\n\033[0;32m", all->last->cmd, "\033[00m\n");
		if (all->last->cmd && ft_strcmp(all->last->cmd, "hist") == 0)
			print_history(all);
		if (all->last->cmd && ft_strcmp("exit", all->last->cmd) == 0)
			break ;
		start_lex(all->last->cmd);
		ft_strdel(&all->save);
		all->last->next = NULL;
	}
	ft_strdel(&all->save);
	end_of_shell(all);
	return (0);
}
