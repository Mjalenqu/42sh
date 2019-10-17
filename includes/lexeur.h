/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexeur.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 13:50:20 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/16 12:51:02 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEXEUR_H
# define LEXEUR_H

# include "../libft/includes/ft_int.h"
# include "../libft/includes/ft_unix.h"
# include "../libft/includes/ft_str.h"
# include "termcaps.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define ENVIRONEMENT 0
# define LOCAL 1
# define ALIAS 2
# define TEMP 3
# define SPE 4

enum		e_token
{
	T_AND,
	T_EXEC_SIM,
	T_OR,
	T_PIPE,
	T_OUT_D,
	T_AG_FDO,
	T_OUT_S,
	T_IN_D,
	T_AG_FDI,
	T_IN_S,
	T_SEMI,
};

typedef struct s_alias	t_alias;
typedef struct s_var	t_var;

typedef struct			s_token
{
	char				*name;
	int					size;
	enum e_token		token;
}						t_token;

typedef struct			s_lexeur
{
	char				*word;
	enum e_token		token;
	char				*redirection;
	char				*fd_in;
	char				*fd_out;
}						t_lexeur;

typedef struct			s_replace
{
	char				*name;
	struct s_replace	*next;
}						t_replace;

typedef struct			s_temp_var
{
	char				*data;
	struct s_temp_var	*next;
}						t_tvar;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                             tool_split.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					token_8_and_5(int *i, int ret, char *str);
void					split_space_find_number(char *str, int *i);
int						check_token_after_number(char *str, int i);
int						double_check(char *str, int i);
void					split_space_basic(char *str, int *i);
void					heredoc_go_next(char *str, int *i, char *tag,
						int *heredoc);
char					*get_tag(char *str, int *i);
char					*fill_res_token(int *tint, int ret, char *str);
int						basic_split_init(char *str, int *tint, int *start,
						int *ret);
int						search_agregator(char *str, int i);
void					split_agregator(char *str, int *i);
/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                             alias_replace.c                                ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					replace_alias_while_fill(char *tmp, int *j,
						int *i, t_alias *alias);
int						replace_alias_while(t_var *var, t_alias *alias);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                             quote_tool.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int						check_red(char *str);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                           replace_tool.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char					*make_string(char **array);
int						check_backslash_var(char *str);
int						check_alias(char *array, t_var *var);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 lexeur.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_lexeur				**start_lex(t_var *var, char *res);
void					free_lexer(t_lexeur **array);
int						find_token(char *buf, int i);
int						cnt_wrd(char *buf);
t_token					g_fill_token[12];

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                            lexeur_tool.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char					*get_fd_in(char *str);
char					*get_fd_out(char *str);
void					fill_struct_fd_in(t_lexeur *res, char *fd_in,
						enum e_token token, char *red);
void					fill_struct_fd_out(t_lexeur *res, char *fd_in,
						enum e_token token, char *fd_out);
char					*ft_del_simple_quote(char *word);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               lexeur_struct.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					fill_struct(t_lexeur *res, char *word,
						enum e_token token, char *red);
t_lexeur				*fill_lex_while(char *buf, int *i, int token);
t_lexeur				*fill_lex_redirection(char **buf,
						int *i, enum e_token token);
void					fill_lex_heredoc(t_lexeur ***array, int *j,
						char **buf, int *i);
void					token_8_and_5(int *i, int ret, char *str);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 fill_lexeur.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char					*change_buf(char *buf);
t_lexeur				**fill_lex(char **buf, t_lexeur **tabe);
void					jump_space(char *buf, int *i);
char					*get_fd_in(char	*str);
void					fill_struct_in(t_lexeur *res, char *fd_in,
						enum e_token token, char *red);
void					fill_struct_out(t_lexeur *res, char *fd_in,
						enum e_token token, char *fd_out);
void					fill_struct(t_lexeur *res, char *word,
						enum e_token token, char *red);
t_lexeur				*fill_lex_redirection(char **buf, int *i,
						enum e_token token);
t_lexeur				*fill_lex_while(char *buf, int *i, int token);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                            fill_lexeur_tool.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char					*change_buf(char *buf);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 back_slash.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					fill_lex_solve_back_slash(char *buf, int *i,
						int *start);
void					cnt_solve_back_slash(char *buf, int *i, int *cnt);
void					del_back_slash(char ***ar);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                             back_slash_end.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					del_back_slash_end(char ***ar);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                           back_slash_tools.c                               ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					cnt_solve_back_slash(char *buf, int *i, int *cnt);
int						back_slash_count(char *str);
int						del_back_slash_simple_quote(int *k, int j, char ***ar);
int						del_back_slash_double_quote(int *k, int j, char ***ar);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 redirection.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char					*fill_redirection(char **buf, int *i);
t_lexeur				**find_input_redirection(t_lexeur ***tabe);
t_lexeur				**check_redirection(t_lexeur ***tabe);
char					*get_fd_out(char *str);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 redirection.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					free_ar_lexeur(t_lexeur ***array);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                double_quote.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					fill_lex_doudle_quote(char *buf, int *i, int *start);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 redirection.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_lexeur				*find_fd(char *buf, int i);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 redirection.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char					**start_split(t_var *var, char *str);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 env_replace.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					replace_var(t_var *env, t_alias *alias);
char					*switch_word(char *str, char *tmp, int i);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 env_replace.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					check_var(t_var *env, char **str);
char					**replace_env(t_var *env, char *str);
int						f_check_var(t_var *env, char *str);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   tool.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char					**split_space(char *str);
void					list_add(t_replace **replace, char *array);
void					free_replace(t_replace *replace);
void					init_replace(t_replace **replace);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                               tool_cnt.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					cnt_size_simple_quote(int *i, int *nb, char *str);
void					cnt_size_double_quote(int *i, int *nb, char *str);
int						cnt_printable_char(int *nb, char *str, int *i);
void					heredoc_go_next_quote(char *str, int *i);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              tool_list.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					free_replace(t_replace *replace);
void					init_replace(t_replace **replace);
void					*get_replace(void *stock, int i);
void					replace_alias(t_alias *alias, t_var *var,
						t_replace *replace);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   quote.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void					remoove_quote(char ***array);
int						check_tok(t_alias *alias, t_var *var,
						t_replace *replace);
void					free_alias(t_alias *alias);
int						remove_env_while(t_alias *alias, t_var *var,
						t_replace *replace);
void					print_lexer(t_lexeur *lex);

#endif
