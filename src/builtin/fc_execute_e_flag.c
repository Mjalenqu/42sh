/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_execute_e_flag.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/25 08:56:49 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 08:28:44 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/termcaps.h"

static int			fill_command_to_send_to_text_editor(t_fc *fc, t_hist *hist,
					int fd)
{
	if (fc->int_first <= fc->int_last)
	{
		while (fc->int_first <= fc->int_last && hist->next && hist->next->next)
		{
			write(fd, hist->cmd, ft_strlen(hist->cmd));
			write(fd, "\n", 1);
			hist = hist->next;
			fc->int_first += 1;
		}
	}
	else if (fc->int_first > fc->int_last)
	{
		while (fc->int_first >= fc->int_last && hist)
		{
			if (hist->next && hist->next->next)
			{
				write(fd, hist->cmd, ft_strlen(hist->cmd));
				write(fd, "\n", 1);
			}
			hist = hist->prev;
			fc->int_first -= 1;
		}
	}
	return (fd);
}

char				**recover_new_cmds_from_tmp(char **new_cmds, int fd, int i,
					int ret)
{
	char			*line;
	t_hist			*hist;
	char			*pwd;

	hist = stock(NULL, 8);
	if (hist->cmd_no > 20)
		new_cmds = (char**)malloc(sizeof(char*) * ((hist->cmd_no + 1) * 2));
	else
		new_cmds = (char**)malloc(sizeof(char*) * 50 + 1);
	line = NULL;
	pwd = ft_strjoinf(getcwd(NULL, 255), "/.tmp", 1);
	fd = open(pwd, O_RDWR | O_APPEND | O_CREAT, 0666);
	while ((ret = get_next_line(fd, &line)))
	{
		if (ft_strlen(line) > 0)
		{
			transform_tab_into_space(line);
			new_cmds[i] = ft_strnew(0);
			new_cmds[i] = ft_strjoinf(new_cmds[i], line, 3);
			i++;
		}
	}
	new_cmds[i] = NULL;
	free(pwd);
	return (new_cmds);
}

void				exec_new_cmds(char **new_cmds)
{
	int				i;
	char			*tmp_cmd;
	t_hist			*hist;
	t_var			*var;

	var = stock(NULL, 6);
	hist = stock(NULL, 8);
	i = 0;
	i = 0;
	while (new_cmds[i])
	{
		var = stock(NULL, 6);
		tmp_cmd = ft_strdup(new_cmds[i]);
		if ((check_error(new_cmds[i])) != -1)
		{
			ft_printf("%s\n", tmp_cmd);
			start_exec(start_lex(stock(NULL, 6), tmp_cmd), stock(NULL, 6));
		}
		i++;
	}
	place_new_cmds_in_history(new_cmds, hist);
}

void				exec_ide_with_tmp_file(t_fc *fc, int fd, char **env)
{
	char			**arg_tmp;
	pid_t			father;
	char			**new_cmds;
	int				i;
	int				ret;

	i = 0;
	ret = 1;
	father = fork();
	arg_tmp = (char**)malloc(sizeof(char*) * 3);
	arg_tmp[0] = ft_strdup(fc->ename);
	arg_tmp[1] = ft_strdup(".tmp");
	arg_tmp[2] = NULL;
	new_cmds = NULL;
	if (father > 0)
	{
		wait(&father);
		new_cmds = recover_new_cmds_from_tmp(new_cmds, fd, i, ret);
		exec_new_cmds(new_cmds);
		ft_free_tab(arg_tmp);
		return ;
	}
	else if (father == 0)
		execve(fc->ename, arg_tmp, env);
}

void				send_e_flag_to_exec(t_fc *fc, t_hist *hist, char **env)
{
	char			*pwd;
	int				fd;

	pwd = getcwd(NULL, 255);
	pwd = ft_strjoinf(pwd, "/.tmp", 1);
	fd = open(pwd, O_RDWR | O_TRUNC | O_CREAT, 0666);
	free(pwd);
	correct_int_first_and_int_last_for_e_flag(fc, hist);
	if (ft_strchr(fc->flags, 'r') != NULL)
		inverse_first_and_last_if_flag_r(fc);
	while (hist->prev && hist->cmd_no + 1 > fc->int_first)
		hist = hist->prev;
	fill_command_to_send_to_text_editor(fc, hist, fd);
	exec_ide_with_tmp_file(fc, fd, env);
}
