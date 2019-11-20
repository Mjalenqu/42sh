/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/03 15:18:39 by mjalenqu     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/04 12:23:39 by mjalenqu    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_STR_H
# define FT_STR_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "ft_unix.h"
# include "ft_mem.h"
# include "ft_int.h"
# include "ft_printf.h"
# include "ft_printf_err.h"

/*
** Get Next Line Struct
*/

# define BUFF_SIZE 5000

typedef struct		s_stock
{
	char			*str;
	int				fd;
	struct s_stock	*next;
}					t_stock;

void				ft_bzero(void *elem, int i);
int					ft_isalpha(int c);
void				ft_isascii(int c);
int					ft_isalnum(char *str);
int					ft_isalnum_underscore(char *str);
int					ft_isspace(int c);
char				*ft_itoa(int i);
char				*ft_itoa_base(int nb, int base);
int					ft_putchar(int c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(const char *s);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putstr(const char *s);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putstr_tab(char **tabe);
char				*ft_strcat(char *dest, char *src);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcpy(char *dest, const char *str);
char				*ft_strncpy(char *dst, const char *str, size_t len);
void				ft_strdel(char **str);
char				*ft_strdup(char *str);
char				*ft_strfdup(char *str);
char				*ft_strndup(char *str, int len);
int					ft_strequ(const char *s1, const char *s2);
char				*ft_strjoin(const char *s1, const char *s2);
void				ft_strjoin_free(char **s1, const char *s2);
void				ft_strjoin_insert(char **s1, char *s2, int i);
int					ft_strlen(const char *str);
char				*ft_strnew(int size);
char				*ft_strrmvi(char *str, int i);
char				*ft_strstr(const char *str, const char *tofind);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strfsub(char *s, unsigned int start, size_t len);
void				*ft_voidrev(void *s);
void				ft_voidswap(void *s, void *d);
void				ft_putcolor(char *s1, char *s2, char *s3);
void				ft_putcolor2(char *s1, char *s2, char *s3, char *s4);
void				ft_put_space(int i);
char				**ft_strsplit(const char *str, char c);
void				ft_free_tab(char **tabe);
int					get_next_line(int fd, char **line);
void				*ft_memset(void *mem, int c, size_t l);
char				*ft_strjoinf(char *s1, char *s2, int mode);
char				*ft_strchr(const char *s, int c);
char				*ft_strcapitalizer(char *str);
char				*ft_copy_part_str(char *str, int i, int usage);
char				*ft_swap_let_string(char *str, int let1, int let2);
char				*ft_strrev(char *str);
void				*ft_secure_free(void *to_free);
int					ft_strstr_case_unsensitive(char *str, char *tofind);
int					ft_strncmp_case_unsensitive(char *s1, char *s2, size_t n);

#endif
