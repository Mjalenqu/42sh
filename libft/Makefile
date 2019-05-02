# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/25 12:55:34 by shthevak     #+#   ##    ##    #+#        #
#    Updated: 2019/04/30 18:17:03 by mjalenqu    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY : all clean fclean re sobj uobj iobj

NAME = libft.a

BLUE=\033[0;38;5;123m
LIGHT_PINK = \033[0;38;5;200m
PINK = \033[0;38;5;198m
DARK_BLUE = \033[0;38;5;110m
GREEN = \033[0;38;5;111m
LIGHT_GREEN = \033[1;38;5;121m
LIGHT_RED = \033[1;31;5;121m
FLASH_GREEN = \033[33;32m
# **************************************************************************** #
#									PATH                                       #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/

SSRC_PATH = $(addprefix $(SRC_PATH), str/)
SOBJ_PATH = $(addprefix $(OBJ_PATH), str/)


USRC_PATH = $(addprefix $(SRC_PATH), unix/)
UOBJ_PATH = $(addprefix $(OBJ_PATH), unix/)

ISRC_PATH = $(addprefix $(SRC_PATH), int/)
IOBJ_PATH = $(addprefix $(OBJ_PATH), int/)

MSRC_PATH = $(addprefix $(SRC_PATH), mem/)
MOBJ_PATH = $(addprefix $(OBJ_PATH), mem/)


# **************************************************************************** #
# 									SRCS                                       #
# **************************************************************************** #

SINC_NAME = ft_str.h
SSRC_NAME = ft_bzero.c ft_isalpha.c ft_isascii.c ft_itoa.c ft_itoa_base.c\
			ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_strncmp.c\
			ft_putstr.c ft_putstr_fd.c ft_putstr_tab.c ft_str_remove_index.c ft_strcat.c ft_strcmp.c\
			ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_strjoin.c\
			ft_strjoin_free.c ft_strjoin_insert.c ft_strlen.c ft_strnew.c\
			ft_strstr.c ft_strsub.c ft_voidrev.c ft_voidswap.c ft_put_space.c\
			ft_strsplit.c ft_free_tab.c get_next_line.c ft_putcolor.c ft_putcolor2.c ft_isspace.c\
			ft_strncpy.c ft_strjoinf.c ft_strchr.c ft_strcapitalizer.c ft_copy_part_str.c\
			ft_swap_let_string.c ft_strrev.c

UINC_NAME = ft_unix.h
USRC_NAME = ft_terminal_h.c ft_terminal_w.c ft_file_exists.c ft_create_file.c\
			ft_execute.c ft_file_arights.c ft_file_rrights.c ft_file_wrights.c\
			ft_file_xrights.c ft_is_exec.c

IINC_NAME = ft_int.h
ISRC_NAME = ft_atoi.c ft_int_len_base.c ft_isdigit.c ft_isxdigit.c ft_putnbr.c\
			ft_putnbr_base.c ft_voidrev.c ft_voidswap.c ft_itoa_base_uns.c check_num_length.c

MINC_NAME = ft_mem.h
MSRC_NAME = ft_memset.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
			ft_memdel.c ft_memmove.c


# **************************************************************************** #
#  									VAR                                        #
# **************************************************************************** #

SOBJ_NAME = $(SSRC_NAME:.c=.o)
SOBJ = $(addprefix $(SOBJ_PATH), $(SOBJ_NAME))
SINC = $(addprefix $(INC_PATH), $(SINC_NAME))

UOBJ_NAME = $(USRC_NAME:.c=.o)
UOBJ = $(addprefix $(UOBJ_PATH), $(UOBJ_NAME))
UINC = $(addprefix $(INC_PATH), $(UINC_NAME))

IOBJ_NAME = $(ISRC_NAME:.c=.o)
IOBJ = $(addprefix $(IOBJ_PATH), $(IOBJ_NAME))
IINC = $(addprefix $(INC_PATH), $(IINC_NAME))

MOBJ_NAME = $(MSRC_NAME:.c=.o)
MOBJ = $(addprefix $(MOBJ_PATH), $(MOBJ_NAME))
MINC = $(addprefix $(INC_PATH), $(MINC_NAME))


# **************************************************************************** #
#  									FLAG                                       #
# **************************************************************************** #

ifndef FLAGS
	FLAGS = -Wall -Werror -Wextra -g3
endif

# **************************************************************************** #
# 									REGLES                                     #
# **************************************************************************** #

all : $(OBJ_PATH) $(NAME)

$(NAME): $(SOBJ) $(UOBJ) $(IOBJ) $(LOBJ) $(MOBJ)
	@ar rcs $(NAME) $(SOBJ) $(UOBJ) $(IOBJ) $(LOBJ) $(MOBJ)
	@echo "\n\033[0m"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH) 2> /dev/null
	@mkdir -p $(SOBJ_PATH) 2> /dev/null
	@mkdir -p $(UOBJ_PATH) 2> /dev/null
	@mkdir -p $(IOBJ_PATH) 2> /dev/null
	@mkdir -p $(MOBJ_PATH) 2> /dev/null

$(SOBJ_PATH)%.o: $(SSRC_PATH)%.c $(SINC)
	@gcc $(FLAGS) -I $(INC_PATH) -o $@ -c $<
	@echo "$(LIGHT_RED).\c"

$(UOBJ_PATH)%.o: $(USRC_PATH)%.c $(UINC)
	@gcc $(FLAGS) -I $(INC_PATH) -o $@ -c $<
	@echo "$(LIGHT_RED).\c"

$(IOBJ_PATH)%.o: $(ISRC_PATH)%.c $(IINC)
	@gcc $(FLAGS) -I $(INC_PATH) -o $@ -c $<
	@echo "$(LIGHT_RED).\c"

$(MOBJ_PATH)%.o: $(MSRC_PATH)%.c $(MINC)
	@gcc $(FLAGS) -I $(INC_PATH) -o $@ -c $<
	@echo "$(LIGHT_RED).\c"

clean: 
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
