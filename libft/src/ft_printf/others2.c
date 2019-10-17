/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   others2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/04 08:54:16 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 09:44:48 by rlegendr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void			init_color_printf(t_color *col)
{
	col->color = NULL;
	col->bold = 0;
	col->underlined = 0;
	col->italic = 0;
	col->text = 0;
	col->back = 0;
	col->blinking = 0;
	col->check = 0;
}

void			print_usage_ft_printf(void)
{
	ft_putstr("\nFT_PRINTF USAGE :\n\n");
	ft_putstr("-	format : %[flags][width][.precision][length][conv_type]\n");
	ft_putstr("\n-	formats available : #, 0, -, +, ' '\n\n");
	ft_putstr("-	length available : h, hh, l, ll\n");
	ft_putstr("\n-	flags available : c (char), s (string), p (pointer), d, i");
	ft_putstr(" (int), f (float), o (octal), u (unsigned int), x, X (hexa), %");
	ft_putstr("(print %)\n\n-	bonus added : b (binary), T (**char), t ");
	ft_putstr("(**int), W(***char), {B.U.I.F.T.blue.S.red.}{eoc} (color)\n\n");
	ft_putstr("-	color : B. = Bold, U. = Underlined, I. = Italic, F. = ");
	ft_putstr("Flashing, T. = Text, S. = Shell (colors : grey, red, green, ");
	ft_putstr("yellow, blue, purple, cyan, white)\n\n");
}
