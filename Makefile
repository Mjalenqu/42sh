# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/04 18:02:46 by mjalenqu     #+#   ##    ##    #+#        #
#    Updated: 2019/11/14 10:20:14 by rlegendr    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = 42sh

LIB_PATH = libft/
LIB_LIB  = libft/libft.a
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./includes/
ALL_INC  = ./includes/$(wildcard *.h)

SRC_LINE = $(addprefix line_edit/,\
				calcul_line.c check_error.c check_input.c control_search_history_calcul_pos.c\
				control_search_history.c control_search_history_calcul_lines.c \
				copy_tools.c copy.c cut.c env.c escape_code.c ft_errno.c\
				history_expansion.c history_expansion_types.c\
				history_expansion_calculate.c\
				history.c initialisation_stock.c input_is_entry.c tools.c\
				input_is_printable_char.c input_is_remove_char.c jump_up_down.c jump.c\
				move_through_history.c print_ans.c search_in_history.c signal.c tab_key_var.c\
				start_termcaps.c tab_key.c tab_key_all_path.c tab_key_auto_complete.c tab_key_current_dir.c\
				tab_key_sort.c tab_key_struct.c tab_key_tools_calcul_print.c tab_key_tools_manip.c\
				 init_alias.c check_for_tilde.c \
				tab_key_auto_complete_tilde.c check_backslash.c \
				token.c token_conditions.c heredoc.c heredoc_send_valid_ans.c heredoc_tools.c\
				init_spe_params.c print_prompt.c resize.c)

SRC_PRINTF = $(addprefix printf_fd/, \
			 	ft_printf_fd.c print_colors_fd.c print_printf_fd.c )

SRC_PRINTF_ERR = $(addprefix printf_error_fd/, \
				 ft_printf_err_fd.c print_colors_err_fd.c print_printf_err_fd.c)

SRC_LEX = $(addprefix lexeur/, \
				back_slash.c back_slash_tools.c error.c error_tool.c\
				fill_lexeur.c lexeur.c redirection.c redirection_tools.c lexeur_tool.c \
				lexeur_struct.c fill_lexeur_tool.c)

SRC_EXEC = $(addprefix exec/, \
				alias.c builtins.c launch_process.c launch_job.c exec.c process.c tools.c \
			job_controll.c job_function.c job_notification.c var.c var_tools.c process_fill.c \
				process_tool.c alias_tools.c free_job.c new_job.c process_file.c \
				alias_reduction.c alias_norme.c exec_tool.c var_norme.c launch_job_process.c \
				job_function_plus_and_minus.c process_heredoc.c redirection_dispatch.c \
				redirection_init_and_normal.c redirection_pipe_aggregator.c redirection_apply.c \
				redirection_files_rights.c zombie.c)

SRC_REP = $(addprefix replace/, \
				alias.c var_replace.c var_tool.c tool_cnt.c tool_list.c replace.c tool.c quote.c\
				alias_tools.c free_file.c alias_change_type.c alias_cnt.c alias_replace.c\
				tool_split.c split_agregator.c quote_tool.c replace_tool.c var_condition_tool.c)

SRC_BUILTIN = $(addprefix builtin/, \
				ft_test.c ft_test_int.c ft_echo.c ft_set.c ft_type.c ft_export.c \
				ft_unset.c fc_free.c ft_fc.c tool.c ft_fg.c ft_bg.c ft_jobs.c \
				ft_jobs_print.c ft_exit.c fc_get_args.c \
				fc_get_flags.c fc_execute_l_flag.c fc_execute_s_flag.c fc_execute_e_flag.c \
				fc_tools.c fc_prepare_e_flag.c fc_s_replace_pattern.c ft_hash.c \
				hash_d_flag.c ft_setenv.c ft_unsetenv.c ft_env.c ft_env_tools.c \
				ft_env_i_flag.c ft_cd.c ft_cd_verif.c ft_cd_prepare_data.c ft_cd_check_cdpath.c \
				tools_bis.c ft_setenv_tool.c ft_env_i_new_env.c\
				ft_fg_bg_plus_and_minus.c ft_shtheme.c ft_cd_error.c fc_list.c\
				fc_prepare_e_flag_tool.c ft_env_i_flag_tool.c ft_fg_bg_tools.c)

SRC_MAIN = $(addprefix main/, main.c init_pos_main.c)

SRC_HASH = $(addprefix hash/, hash.c hash_tools.c hash_path.c hash_prepare_error.c)

SRC_NAME = $(SRC_EXEC) $(SRC_LEX) $(SRC_LINE) $(SRC_MAIN) $(SRC_REP) $(SRC_BUILTIN) $(SRC_HASH) $(SRC_PRINTF) $(SRC_PRINTF_ERR)

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = termcaps.h alias.h builtin.h check_error.h exec.h hash.h launch.h \
		   lexeur.h

INC = $(addprefix $(INC_PATH), $(INC_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

FLAG += -Wall -Werror -Wextra -Og -g3 #-fsanitize=address #-fsanitize=undefined
FLAG_END = -lcurses
NORME = norminette

WHITE_BOLD = \033[37m
BLUE=\033[0;38;5;123m
DARK_BLUE = \033[0;38;5;110m
GREEN = \033[0;32m
GREEN_BOLD = \033[1;32m
LIGHT_GREEN = \033[1;38;5;121m
LIGHT_YELLOW = \033[1;33;5;121m
LIGHT_RED = \033[1;31;5;121m
FLASH_GREEN = \033[33;32m
YELLOW = \033[1;33m
RED = \033[1;31m
RESET = \033[0m

all:
	@echo ""
	@make -C $(LIB_PATH)
	@make $(NAME)
	@echo ""

$(NAME) : $(OBJ) Makefile $(LIB_LIB)
	@echo  "			\033[2K\r$(YELLOW)42sh:	$(GREEN_BOLD)loaded$(RESET)"
	@gcc $(FLAG) -o $@ $(OBJ) $(FLAG_END) $(LIB_LIB) -I include

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	@if test ! -d $(dir $@); then mkdir -p $(dir $@); fi
	@gcc $(FLAG) -g -I $(INC_PATH) -o $@ -c $<
	@printf "\033[2K\r$(YELLOW)42sh:	\033[37m$<\033[36m \033[0m"

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ_PATH)
	@echo "$(YELLOW)42sh:	$(RED)object files deleted$(RESET)"

fclean: clean
	@make -C libft/ fclean
	@rm -rf $(NAME)
	@echo "$(YELLOW)42sh:	$(RED)executable file deleted$(RESET)"

batman: all
	@echo "$(YELLOW)                   ..oo800ooo..                    ..ooo008oo.. "
	@echo "                .o888888888'                          '888888888o. "
	@echo "             .o888888888'            .   .              '888888888o. "
	@echo "          .o8888888888~             /8   8\              ~8888888888o. "
	@echo "        .{88888888888.              8\___/8               .88888888888}. "
	@echo "       o8888888888888              .8888888.               8888888888888o "
	@echo "      888888888888888              888888888               888888888888888 "
	@echo "     o888888888888888.             o8888888o              .888888888888888o "
	@echo "     88888888     8888.           o{8888888}o            .888888    8888888 "
	@echo "    ^8888888  88  88888.         J88888888888L          .88888  8888  88888^ "
	@echo "    !888888  888  8888888oo..oo88888888888888888oo..oo88888888888888  88888! "
	@echo "    {88888  8888  888888888888888888888888888888888888888888888888  8888888} "
	@echo "    688888          88888888888888888888888888888888888888888888  888888888? "
	@echo "    '88888888888  88888888888888888888888888888888888888888888  88888888888' "
	@echo "     o8888888888  8888888888888888888888888888888888888888888         8888o "
	@echo "      88888888888888;'~'^Y8887^''o88888888888o''^Y8887^'~';888888888888888 "
	@echo "      '88888888888'       '8'     '888888888'    '8'       '888888888888' "
	@echo "       !8888888887         !       '8888888'      !         V888888888! "
	@echo "        ^o888888!                   '88888'                  !888888o^ "
	@echo "          ^88888'                    88888                   '88888^ "
	@echo "            'o888'                   ^888'                  '888o' "
	@echo "              ~888.                   888                  .888~ "
	@echo "                '8;.                  '8'                 .;8' "
	@echo "                   '.                  !                 .' $(RESET)"


re : fclean all
