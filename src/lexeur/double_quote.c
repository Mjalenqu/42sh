/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   double_quote.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/15 13:55:20 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/20 18:04:03 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/lexeur.h"

void		fill_lex_doudle_quote(char *buf, int *i, int *start)
{
	(*i)++;
	*start = *i;
	while (buf[*i] && buf[*i] != '"')
		(*i)++;
}
