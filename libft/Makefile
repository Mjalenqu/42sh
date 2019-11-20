# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mjalenqu <mjalenqu@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/25 12:55:34 by mjalenqu     #+#   ##    ##    #+#        #
#    Updated: 2019/11/05 15:04:16 by mjalenqu    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY : all clean fclean re sobj uobj iobj

NAME = libft.a

BLUE=\033[0;38;5;123m
LIGHT_PINK = \033[0;38;5;200m
PINK = \033[0;38;5;198m
DARK_BLUE = \033[1;38;5;110m
GREEN = \033[1;32;111m
LIGHT_GREEN = \033[1;38;5;121m
LIGHT_RED = \033[0;38;5;110m
FLASH_GREEN = \033[33;32m
WHITE_BOLD = \033[37m

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

PSRC_PATH = $(addprefix $(SRC_PATH), ft_printf/)
POBJ_PATH = $(addprefix $(OBJ_PATH), ft_printf/)

PESRC_PATH = $(addprefix $(SRC_PATH), ft_printf_err/)
PEOBJ_PATH = $(addprefix $(OBJ_PATH), ft_printf_err/)

# **************************************************************************** #
# 									SRCS                                       #
# **************************************************************************** #

SINC_NAME = ft_str.h
SSRC_NAME = ft_bzero.c ft_isalpha.c ft_isascii.c ft_itoa.c ft_itoa_base.c\
			ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_strncmp.c\
			ft_putstr.c ft_putstr_fd.c ft_putstr_tab.c ft_str_remove_index.c ft_strcat.c ft_strcmp.c\
			ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_strjoin.c\
			ft_strjoin_free.c ft_strjoin_insert.c ft_strlen.c ft_strnew.c\
			ft_strstr.c ft_strsub.c ft_strfsub.c ft_voidrev.c ft_voidswap.c ft_put_space.c\
			ft_strsplit.c ft_free_tab.c get_next_line.c ft_putcolor.c ft_putcolor2.c ft_isspace.c\
			ft_strncpy.c ft_strjoinf.c ft_strchr.c ft_strcapitalizer.c ft_copy_part_str.c\
			ft_swap_let_string.c ft_strrev.c ft_secure_free.c ft_strndup.c ft_isalnum_underscore.c\
			ft_strstr_case_unsensitive.c ft_strncmp_case_unsensitive.c ft_strfdup.c ft_isalnum.c

UINC_NAME = ft_unix.h
USRC_NAME = ft_terminal_h.c ft_terminal_w.c ft_file_exists.c ft_create_file.c\
			ft_execute.c ft_file_arights.c ft_file_rrights.c ft_file_wrights.c\
			ft_file_xrights.c ft_is_exec.c is_the_same_letter_unsensitive.c

IINC_NAME = ft_int.h
ISRC_NAME = ft_atoi.c ft_int_len_base.c ft_isdigit.c ft_isxdigit.c ft_putnbr.c\
			ft_putnbr_base.c ft_voidrev.c ft_voidswap.c ft_itoa_base_uns.c check_num_length.c

MINC_NAME = ft_mem.h
MSRC_NAME = ft_memset.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
			ft_memdel.c ft_memmove.c ft_free_void.c ft_tabdel.c ft_malloc.c

PINC_NAME = ft_printf.h
PSRC_NAME = add_conversion.c add_flag2.c add_flags.c bonus_conversion_type_1.c\
			bonus_conversion_type_2.c bonus_conversion_type_3.c conversion_type.c\
			conversion_type2.c determ_data.c ft_printf.c handle_flags_order.c\
			handle_float.c handle_prec_and_width.c others.c others2.c \
			print_colors.c print_printf.c

PEINC_NAME = ft_printf_err.h
PESRC_NAME = add_conversion.c add_flag2.c add_flags.c bonus_conversion_type_1.c\
			bonus_conversion_type_2.c bonus_conversion_type_3.c conversion_type.c\
			conversion_type2.c determ_data.c ft_printf.c handle_flags_order.c\
			handle_float.c handle_prec_and_width.c others.c others2.c \
			print_colors.c print_printf.c

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

POBJ_NAME = $(PSRC_NAME:.c=.o)
POBJ = $(addprefix $(POBJ_PATH), $(POBJ_NAME))
PINC = $(addprefix $(INC_PATH), $(PINC_NAME))

PEOBJ_NAME = $(PESRC_NAME:.c=.o)
PEOBJ = $(addprefix $(PEOBJ_PATH), $(PEOBJ_NAME))
PEINC = $(addprefix $(INC_PATH), $(PEINC_NAME))

# **************************************************************************** #
#  									FLAG                                       #
# **************************************************************************** #

FLAGS = -Wall -Werror -Wextra -O3 -g3 #-fsanitize=address#-fsanitize=undefined 

# **************************************************************************** #
# 									REGLES                                     #
# **************************************************************************** #

all : $(NAME)

$(NAME): $(SOBJ) $(UOBJ) $(IOBJ) $(LOBJ) $(MOBJ) $(POBJ) $(PEOBJ)
	@ar rcs $(NAME) $(SOBJ) $(UOBJ) $(IOBJ) $(LOBJ) $(MOBJ) $(POBJ) $(PEOBJ)
	@echo "	\033[2K\r$(DARK_BLUE)libft:	$(GREEN)loaded\033[0m"

$(SOBJ_PATH)%.o: $(SSRC_PATH)%.c $(SINC)
	@if test ! -d $(dir $@); then mkdir -p $(dir $@); fi
	@gcc $(FLAGS) -I $(INC_PATH) -o $@ -c $<
	@printf "\033[2K\r$(DARK_BLUE)libft:	\033[37m$<\033[36m \033[0m"

$(UOBJ_PATH)%.o: $(USRC_PATH)%.c $(UINC)
	@if test ! -d $(dir $@); then mkdir -p $(dir $@); fi
	@gcc $(FLAGS) -I $(INC_PATH) -o $@ -c $<
	@printf "\033[2K\r$(DARK_BLUE)libft:	\033[37m$<\033[36m \033[0m"

$(IOBJ_PATH)%.o: $(ISRC_PATH)%.c $(IINC)
	@if test ! -d $(dir $@); then mkdir -p $(dir $@); fi
	@gcc $(FLAGS) -I $(INC_PATH) -o $@ -c $<
	@printf "\033[2K\r$(DARK_BLUE)libft:	\033[37m$<\033[36m \033[0m"

$(MOBJ_PATH)%.o: $(MSRC_PATH)%.c $(MINC)
	@if test ! -d $(dir $@); then mkdir -p $(dir $@); fi
	@gcc $(FLAGS) -I $(INC_PATH) -o $@ -c $<
	@printf "\033[2K\r$(DARK_BLUE)libft:	\033[37m$<\033[36m \033[0m"

$(POBJ_PATH)%.o: $(PSRC_PATH)%.c $(PINC)
	@if test ! -d $(dir $@); then mkdir -p $(dir $@); fi
	@gcc $(FLAGS) -I $(INC_PATH) -o $@ -c $<
	@printf "\033[2K\r$(DARK_BLUE)libft:	\033[37m$<\033[36m \033[0m"

$(PEOBJ_PATH)%.o: $(PESRC_PATH)%.c $(PEINC)
	@if test ! -d $(dir $@); then mkdir -p $(dir $@); fi
	@gcc $(FLAGS) -I $(INC_PATH) -o $@ -c $<
	@printf "\033[2K\r$(DARK_BLUE)libft:	\033[37m$<\033[36m \033[0m"

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
