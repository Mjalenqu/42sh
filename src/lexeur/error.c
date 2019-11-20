/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/02 16:15:56 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:19 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/check_error.h"
#include "../../includes/lexeur.h"

int		syntax_print_error(int token)
{
	ft_printf_err("42sh: syntax {B.T.red.} error{eoc}");
	ft_printf_err(" near unexpected token `%s`\n", g_fill_token[token].name);
	return (-1);
}

int		check_double_token(char *str, int i, int token)
{
	int		token2;

	i += g_fill_token[token].size;
	jump_space(str, &i);
	token2 = find_token(str, i);
	if ((token == 4 || token == 5 || token == 6 || token == 7 || token == 8
	|| token == 9) && (token2 == 4 || token2 == 5 || token2 == 6 || token2 == 7
	|| token2 == 8 || token2 == 9))
		return (syntax_print_error(token2));
	if (token2 != -1 && token2 != 4 && token2 != 5 && token2 != 6
	&& token2 != 7 && token2 != 8 && token2 != 9)
		return (syntax_print_error(token2));
	return (0);
}

int		check_is_end(char *str, int i)
{
	i += g_fill_token[7].size;
	jump_space(str, &i);
	if (!str[i])
		return (0);
	return (1);
}

int		check_error_no_backslash(char *str, int *i)
{
	int		token;

	token = find_token(str, *i);
	if (token != -1)
		if (check_double_token(str, *i, token))
			return (-1);
	if (token == 7 && check_is_end(str, *i))
	{
		error_heredoc_go_next(str, i);
		token = find_token(str, *i);
	}
	if (token == 0 || token == 1 || token == 10
	|| token == 2 || token == 3)
		if (first_check(str, *i, token))
			return (-1);
	if (token == 9 || token == 6 || token == 8 || token == 5
	|| token == 4 || token == 7)
		if (second_check(str, *i, token))
			return (-1);
	if (token != -1)
		(*i) += g_fill_token[token].size;
	else if (str[*i] != '\0')
		(*i)++;
	return (0);
}

int		check_error(char *str)
{
	int		i;

	i = 0;
	if (ft_strcmp(str, "") == 0)
		return (-1);
	while (str[i])
	{
		jump_space(str, &i);
		if ((str[i] == '"' && !odd_backslash(i, str))
		|| (str[i] == '\'' && !odd_backslash(i, str)))
			moove_next_quote(str[i], str, &i);
		if (!odd_backslash(i, str))
		{
			if (check_error_no_backslash(str, &i) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}
