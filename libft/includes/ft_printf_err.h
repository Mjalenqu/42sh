/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf_err.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dcoat <marvin@le-101.fr>                   +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/07 19:51:31 by dcoat        #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 14:13:48 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_ERR_H
# define FT_PRINTF_ERR_H

# include <stdarg.h>
# include "ft_str.h"
# include "ft_unix.h"
# include "ft_mem.h"
# include "ft_int.h"
# include "ft_printf.h"

/*
** STRUCTURE CONTAINING ALL THE POSSIBLE ARGUMENTS OF PRINTF
*/

typedef struct				s_dataerr
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
}							t_dataerr;

typedef struct				s_lengtherr
{
	char					*flags;
	char					*nb;
	char					*length;
	char					*conv;
}							t_lengtherr;

typedef struct				s_floaterr
{
	unsigned long long		nb_int;
	int						prec;
	char					*num;
	char					*tmp;
	long double				nb_float;
	size_t					left_length;
}							t_floaterr;

typedef struct				s_taberr
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
}							t_taberr;

typedef struct				s_colorerr
{
	char					*color;
	int						bold;
	int						underlined;
	int						italic;
	int						blinking;
	int						text;
	int						back;
	int						check;
}							t_colorerr;
/*
**		FT_PRINTF.C
*/

int							ft_printf_err(const char *format, ...);
int							crossing_pourcent_err(char *format, t_dataerr *data,
							int i,
							va_list va);
char						*fill_string_output_err(char *format, char *output,
							int i);
int							is_contained_in_err(char *format, char *compare,
							int i);
int							count_all_datas_err(char *format, int i);

/*
**		DETERM_DATA.C
*/

int							determ_flag_and_width_err(t_dataerr *data,
							char *format, int i);
char						*determ_data_err(char *format, t_dataerr *data,
							va_list va, int i);
char						determ_conv_err(t_dataerr *data, char conv,
							char *format, int i);
char						*add_char_end_string_err(char *dest, char *lett,
							int i);
char						*add_char_begin_string_err(char *dest, char *lett);

/*
**		ADD_CONVERSION.C
*/

int							add_conv_2_err(t_dataerr *data, char **arg,
							char *output);
char						*add_conversion_output_err(t_dataerr *data,
							char *output,
							va_list va, int tmp_args_nb);
char						*conversion_type_err(t_dataerr *data, va_list va);
char						*backslash_strjoin_err(char *s1, char *s2,
							t_dataerr data);

/*
**		CONVERSION_TYPE.C 1 && 2 && BONUS
*/

char						*c_conv_err(va_list va, t_dataerr *data);
char						*s_conv_err(va_list va, t_dataerr *data);
char						*p_conv_err(va_list va, t_dataerr *data);
char						*f_conv_err(va_list va, t_dataerr *data);
char						*d_conv_err(va_list va, t_dataerr *data);
char						*o_conv_err(va_list va, t_dataerr *data);
char						*u_conv_err(va_list va, t_dataerr *data);
char						*x_conv_err(va_list va, t_dataerr *data);
char						*upper_x_conv_err(va_list va, t_dataerr *data);
char						*pourcent_conv_err(t_dataerr *data);
char						*b_conv_err(va_list va, t_dataerr *data);
char						*flag_binary_err(t_dataerr *data, char *num, int i,
							unsigned long long nb);
char						*split_binary_err(char *num, int i);
char						*upper_t_conv_err(va_list va, t_dataerr *data);
char						*upper_t_conv_2_err(t_taberr tab, t_dataerr *data);
char						*t_conv_err(va_list va, t_dataerr *data);
char						*t_conv_2_err(t_taberr tab, t_dataerr *data);
void						t_conv_3_err(t_taberr *tab, t_dataerr *data);
char						*upper_w_conv_err(va_list va, t_dataerr *data);
char						*upper_w_conv_2_err(t_taberr *t, t_dataerr *data);
/*
**		ADD_FLAGS.C
*/

char						*add_flag_to_conv_err(t_dataerr data, char *arg,
							int i);
char						*flag_diez_err(t_dataerr *data, char *arg);
char						*flag_minus_err(t_dataerr data, char *arg, int i);
char						*flag_zero_err(t_dataerr data, char *arg);

/*
**		ADD_FLAG2.C
*/

char						*flag_zero_err(t_dataerr data, char *arg);
char						*flag_minus_err(t_dataerr data, char *arg, int i);

/*
**		HANDLE_FLOAT.C
*/

void						fill_num_err(t_floaterr *flt, t_dataerr *data);
int							change_round_num_err(t_floaterr *flt, int i);
char						*round_num_err(t_floaterr flt);
char						*handle_float_err(long double nb, t_dataerr *data);
int							determ_prec_err(t_dataerr data);

/*
**		HANDLE_PREC_AND_WIDTH
*/

char						*add_prec_to_string_err(t_dataerr data, char *arg);
char						*add_prec_to_pointer_err(t_dataerr data, char *arg);
char						*handle_prec_err(t_dataerr data, char *arg);
char						*handle_width_err(t_dataerr data, char *arg);

/*
**		HANDLE_FLAGS_ORDER
*/

char						*handle_plus_minus_with_zero_err(t_dataerr data,
							char *arg);

/*
**		PRINT_PRINTF
*/

int							check_if_color_err(t_dataerr *d, int i);
int							print_printf_err(t_dataerr *data, int i);

/*
**		PRINT_COLORS
*/

int							handle_colors_err(t_dataerr *data, int i, int tmp);
int							search_color_err(int i, char *output, int usage);
int							add_color_to_output_err(t_dataerr *data,
							t_colorerr col, int i);
int							check_color_code_err(t_dataerr *d, t_colorerr *col,
							int i, int check);
/*
**		OTHERS.C 1 && 2
*/

t_dataerr					*init_data_printf_err(t_dataerr *data);
long						*init_tab_arg_nb_err(t_dataerr data);
char						*free_strjoin_err(char *str1, char *str2);
int							check_non_valid_conv_err(t_dataerr *data);
void						free_data_err(t_dataerr *data, int usage);
void						init_color_printf_err(t_colorerr *col);
void						print_usage_ft_printf_err();

#endif
