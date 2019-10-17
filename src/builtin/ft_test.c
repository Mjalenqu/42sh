/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_test.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/15 12:55:43 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/15 15:49:14 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/builtin.h"

int			test_simple_operator(char *type, struct stat s_type)
{
	if (ft_strcmp(type, "-c") == 0)
		return ((s_type.st_mode & S_IFMT) == S_IFCHR) ? 0 : 1;
	if (ft_strcmp(type, "-d") == 0)
		return ((s_type.st_mode & S_IFMT) == S_IFDIR) ? 0 : 1;
	if (ft_strcmp(type, "-f") == 0)
		return ((s_type.st_mode & S_IFMT) == S_IFREG) ? 0 : 1;
	if (ft_strcmp(type, "-L") == 0)
		return (S_ISLNK(s_type.st_mode & S_IFMT)) ? 0 : 1;
	if (ft_strcmp(type, "-p") == 0)
		return ((s_type.st_mode & S_IFMT) == S_IFIFO) ? 0 : 1;
	if (ft_strcmp(type, "-S") == 0)
		return ((s_type.st_mode & S_IFMT) == S_IFSOCK) ? 0 : 1;
	if (ft_strcmp(type, "-s") == 0)
		return (s_type.st_size > 0 ? 0 : 1);
	if (ft_strcmp(type, "-g") == 0)
		return (s_type.st_mode & S_ISGID) ? 0 : 1;
	if (ft_strcmp(type, "-u") == 0)
		return (s_type.st_mode & S_ISUID) ? 0 : 1;
	if (ft_strcmp(type, "-r") == 0)
		return (s_type.st_mode & S_IRUSR) ? 0 : 1;
	if (ft_strcmp(type, "-w") == 0)
		return (s_type.st_mode & S_IWUSR) ? 0 : 1;
	if (ft_strcmp(type, "-x") == 0)
		return (s_type.st_mode & S_IXUSR) ? 0 : 1;
	return (0);
}

int			simple_operator(char *type, char *name, int *error)
{
	struct stat s_type;

	if (type[0] != '-' && (*error = 1))
	{
		ft_printf_err("test: unknown condition: %s\n", type);
		return (2);
	}
	if (ft_strlen(type) < 2 && (*error = 1))
	{
		ft_printf_err("42sh: parse error: condition expected: %s\n", type);
		return (2);
	}
	if (!ft_strchr("ebcdfLpSsgurwx", type[1]) || ft_strlen(type) > 2)
	{
		*error = 1;
		ft_printf_err("test: unknown condition: %s\n", type);
		return (2);
	}
	if (lstat(name, &s_type) == -1 && (*error = 1))
		return (1);
	if (ft_strcmp(type, "-e") == 0)
		return (0);
	if (ft_strcmp(type, "-b") == 0)
		return (S_ISBLK(s_type.st_mode) ? 0 : 1);
	return (test_simple_operator(type, s_type));
}

int			ft_return(void)
{
	ft_printf_err("test: too many arguments\n");
	return (2);
}

int			ft_test_argv(char **argv)
{
	int		i;
	int		inv;
	int		error;

	error = 0;
	i = 0;
	inv = 0;
	if (ft_tabclen(argv) <= 2)
		return (0);
	if (ft_strcmp(argv[1], "-z") == 0 && ft_tabclen(argv) < 4)
		return (argv[2] == NULL || ft_strlen(argv[2]) == 0 ? 0 : 1);
	if (ft_strcmp(argv[1], "!") == 0 && ft_tabclen(argv) < 6 && (inv = 1))
		argv++;
	else if (ft_tabclen(argv) == 3)
		i = simple_operator(argv[1], argv[2], &error);
	else if (ft_tabclen(argv) == 4 && is_comp(argv[2]) == 1)
		i = comp_operator(argv[1], argv[2], argv[3], &error);
	else if (ft_tabclen(argv) >= 4)
		return (ft_return());
	if (inv == 1 && error == 0)
		i = (i == 0) ? 1 : 0;
	return (i);
}

int			ft_test(t_process *p, t_var **var)
{
	int ret;

	var = NULL;
	if (p->cmd[1] == NULL)
		return (1);
	ret = ft_test_argv(p->cmd);
	return (ret);
}
