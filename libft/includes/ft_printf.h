/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dcoat <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/07 19:51:31 by dcoat        #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 12:56:30 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "ft_str.h"
# include "ft_unix.h"
# include "ft_mem.h"
# include "ft_int.h"

/*
** STRUCTURE CONTAINING ALL THE POSSIBLE ARGUMENTS OF PRINTF
*/

typedef struct				s_data
{
	char					*output;
	int						args_nb;
	long					*tab_arg_nb;
	char					*flag;
	int						plus;
	int						flag_minus;
	int						minus;
	int						space;
	int						zero;
	int						diez_length;
	int						backslash;
	char					conv;
	int						conv_type;
	char					*tmp_width;
	int						width;
	int						prec_dot;
	char					*tmp_prec;
	int						prec;
	char					*length;
	int						f_inf;
	int						f_nan;
	char					*code;
	char					*last_color;
}							t_data;

typedef struct				s_length
{
	char					*flags;
	char					*nb;
	char					*length;
	char					*conv;
}							t_length;

typedef struct				s_float
{
	unsigned long long		nb_int;
	int						prec;
	char					*num;
	char					*tmp;
	long double				nb_float;
	size_t					left_length;
}							t_float;

typedef struct				s_tab
{
	char					**init_tab;
	char					***tab;
	int						**int_tab;
	char					*res;
	int						i;
	int						j;
	int						k;
	int						flag_space;
	int						len;
	int						diff;
	int						biggest;
	int						length;
	int						width;
}							t_tab;

typedef struct				s_color
{
	char					*color;
	int						bold;
	int						underlined;
	int						italic;
	int						blinking;
	int						text;
	int						back;
	int						check;
}							t_color;
/*
**		FT_PRINTF.C
*/

int							ft_printf(const char *format, ...);
int							crossing_pourcent(char *format, t_data *data, int i,
							va_list va);
char						*fill_string_output(char *format, char *output,
							int i);
int							is_contained_in(char *format, char *compare, int i);
int							count_all_datas(char *format, int i);

/*
**		DETERM_DATA.C
*/

int							determ_flag_and_width(t_data *data, char *format,
							int i);
char						*determ_data(char *format, t_data *data, va_list va,
							int i);
char						determ_conv(t_data *data, char conv, char *format,
							int i);
char						*add_char_end_string(char *dest, char *lett, int i);
char						*add_char_begin_string(char *dest, char *lett);

/*
**		ADD_CONVERSION.C
*/

int							add_conv_2(t_data *data, char **arg, char *output);
char						*add_conversion_output(t_data *data, char *output,
							va_list va, int tmp_args_nb);
char						*conversion_type(t_data *data, va_list va);
char						*backslash_strjoin(char *s1, char *s2, t_data data);

/*
**		CONVERSION_TYPE.C 1 && 2 && BONUS
*/

char						*c_conv(va_list va, t_data *data);
char						*s_conv(va_list va, t_data *data);
char						*p_conv(va_list va, t_data *data);
char						*f_conv(va_list va, t_data *data);
char						*d_conv(va_list va, t_data *data);
char						*o_conv(va_list va, t_data *data);
char						*u_conv(va_list va, t_data *data);
char						*x_conv(va_list va, t_data *data);
char						*upper_x_conv(va_list va, t_data *data);
char						*pourcent_conv(t_data *data);
char						*b_conv(va_list va, t_data *data);
char						*flag_binary(t_data *data, char *num, int i,
							unsigned long long nb);
char						*split_binary(char *num, int i);
char						*upper_t_conv(va_list va, t_data *data);
char						*upper_t_conv_2(t_tab tab, t_data *data);
char						*t_conv(va_list va, t_data *data);
char						*t_conv_2(t_tab tab, t_data *data);
void						t_conv_3(t_tab *tab, t_data *data);
char						*upper_w_conv(va_list va, t_data *data);
char						*upper_w_conv_2(t_tab *t, t_data *data);
/*
**		ADD_FLAGS.C
*/

char						*add_flag_to_conv(t_data data, char *arg, int i);
char						*flag_diez(t_data *data, char *arg);
char						*flag_minus(t_data data, char *arg, int i);
char						*flag_zero(t_data data, char *arg);

/*
**		ADD_FLAG2.C
*/

char						*flag_zero(t_data data, char *arg);
char						*flag_minus(t_data data, char *arg, int i);

/*
**		HANDLE_FLOAT.C
*/

void						fill_num(t_float *flt, t_data *data);
int							change_round_num(t_float *flt, int i);
char						*round_num(t_float flt);
char						*handle_float(long double nb, t_data *data);
int							determ_prec(t_data data);

/*
**		HANDLE_PREC_AND_WIDTH
*/

char						*add_prec_to_string(t_data data, char *arg);
char						*add_prec_to_pointer(t_data data, char *arg);
char						*handle_prec(t_data data, char *arg);
char						*handle_width(t_data data, char *arg);

/*
**		HANDLE_FLAGS_ORDER
*/

char						*handle_plus_minus_with_zero(t_data data,
							char *arg);

/*
**		PRINT_PRINTF
*/

int							check_if_color(t_data *d, int i);
int							print_printf(t_data *data, int i);

/*
**		PRINT_COLORS
*/

int							handle_colors(t_data *data, int i, int tmp);
int							search_color(int i, char *output, int usage);
int							add_color_to_output(t_data *data, t_color col,
							int i);
int							check_color_code(t_data *d, t_color *col, int i,
							int check);
/*
**		OTHERS.C 1 && 2
*/

t_data						*init_data_printf(t_data *data);
long						*init_tab_arg_nb(t_data data);
char						*free_strjoin(char *str1, char *str2);
int							check_non_valid_conv(t_data *data);
void						free_data(t_data *data, int usage);
void						init_color_printf(t_color *col);
void						print_usage_ft_printf();

#endif
