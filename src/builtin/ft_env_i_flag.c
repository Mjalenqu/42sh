/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env_i_flag.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 07:50:21 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 15:47:12 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/builtin.h"

static int		fill_new_env(t_process *p, int i, t_var **new_env,
		t_var **head)
{
	char		**new_env_var;

	if (ft_strchr(p->cmd[i], '=') != NULL)
	{
		new_env_var = ft_strsplit(p->cmd[i], '=');
		if ((new_env_var[0] == NULL && new_env_var[1] == NULL) ||
				p->cmd[i][0] == '=')
		{
			ft_free_tab(new_env_var);
			ft_printf_err("42sh: env: invalid argument");
			return (-2);
		}
		if (*new_env == NULL)
		{
			*head = add_list_back_env(*new_env);
			*new_env = *head;
		}
		else
			*new_env = add_list_back_env(*new_env);
		fill_new_link_in_env(*new_env, new_env_var);
		free(new_env_var);
		if (!p->cmd[i + 1])
			return (-1);
	}
	return (0);
}

static void		interpret_env_cmd(t_process *p, int i, char *new_cmd,
				t_var *head)
{
	t_var		*old_env;

	old_env = stock(NULL, 6);
	new_cmd = ft_strnew(0);
	while (p->cmd[i])
	{
		new_cmd = ft_strjoinf(new_cmd, p->cmd[i], 1);
		new_cmd = ft_strjoinf(new_cmd, " ", 1);
		i++;
	}
	if (check_error(new_cmd) != -1)
	{
		stock(head, 5);
		start_exec(start_lex(head, new_cmd), head);
		stock(old_env, 5);
	}
}

int				find_if_cmd_is_builtin(t_process *p)
{
	int			i;

	i = 2;
	while (p->cmd[i] && ft_strchr(p->cmd[i], '=') != NULL)
		i++;
	if (p->cmd[i] && (ft_strcmp(p->cmd[i], "fc") == 0 ||
	ft_strcmp(p->cmd[i], "set") == 0 || ft_strcmp(p->cmd[i], "unset") == 0 ||
	ft_strcmp(p->cmd[i], "export") == 0))
	{
		ft_printf_err("env: %s: No such file or directory\n", p->cmd[i]);
		return (1);
	}
	return (0);
}

int				go_through_process_cmd_tool(int ret, t_var **new_env,
t_var **head)
{
	if (ret == -2)
		return (0);
	print_new_env(new_env, head);
	return (1);
}

int				go_through_process_cmd(t_process *p, t_var **new_env,
				t_var **head, int ret)
{
	int			i;

	i = 1;
	if (find_if_cmd_is_builtin(p) == 1)
		return (0);
	while (p->cmd[++i])
	{
		if (ft_strchr(p->cmd[i], '=') != NULL)
		{
			if ((ret = fill_new_env(p, i, new_env, head)) <= -1)
			{
				if (!go_through_process_cmd_tool(ret, new_env, head))
					return (-1);
				break ;
			}
		}
		else if (p->cmd[i])
		{
			*new_env = *head;
			interpret_env_cmd(p, i, NULL, *new_env);
			break ;
		}
	}
	return (0);
}
