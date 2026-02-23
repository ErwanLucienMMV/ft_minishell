# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 13:32:07 by abarthes          #+#    #+#              #
#    Updated: 2026/02/23 16:50:16 by abarthes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m
MAKEFLAGS += --no-print-directory
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

# Detect Homebrew readline prefix (empty if not installed)
READLINE_PREFIX := $(shell brew --prefix readline 2>/dev/null || true)

# ifeq ($(READLINE_PREFIX),)
# READLINE_INCLUDES :=
# READLINE_LIBS := -lreadline -ledit
# else
READLINE_INCLUDES := -I$(READLINE_PREFIX)/include
READLINE_LIBS := -L$(READLINE_PREFIX)/lib -lreadline -lcurses
# endif

SRC =	terminal/terminal.c parser/tokenize.c parser/sanitize.c \
		parser/sanitize_debug.c \
		parser/sanitize_individual_token.c parser/parser_check_its_quotes.c \
		parser/parser_check_its.c parser/parser_list_operations.c \
		buildins/buildins.c \
		buildins/buildin_exit.c buildins/utils_exit.c buildins/buildin_envpath.c \
		buildins/buildin_unset_export.c buildins/buildin_cd.c \
		envpath/envpath.c envpath/envp_utils.c parser/utils.c \
		envpath/envp_operations.c \
		expand/expand.c expand/expand_plain_text.c expand/expand_d_quote.c \
		expand/expand_s_quotes.c expand/nodes_operations.c \
		expand/checks_for_expand.c expand/calculate_env_size.c \
		expand/add_empty_nodes_to_their_next.c expand/expand_env_var.c \
		signals/signals.c files_handler/fhandler.c here_doc/here_doc.c \
		execve/execve.c execve/utils.c execve/find_command.c \
		execve/execve_piped.c execve/execve_debug.c \
		execve/parse_command.c execve/execve_checks.c execve/execve_children.c \
		execve/free_our_stuff.c execve/execve_piped_redirections.c \
		execve/free_structures.c \
		execve/parse_commands_files.c execve/execve_without_pipe.c \
		execve/execve_no_pipes_redirections.c \
		terminal/terminal_debug.c terminal/terminal_utils_handlers.c \
		buildins/buildin_echo.c \
		terminal/terminal_checks.c \
		errors/error.c errors/error2.c expand/utils.c

OBJ = $(SRC:.c=.o)

NAME = minishell
LIBFT= libft/libft.a

all: $(NAME) $(LIBFT)

debug: CFLAGS += -g -D IS_DEBUG=1

debug: re

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(YELLOW)[MINISHELL] $(GREEN).o created $(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) \
	-Llibft -lft $(READLINE_LIBS) \
	-o $(NAME)
	@echo "$(YELLOW)[MINISHELL] $(GREEN)executable created$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft

clean:
	@rm -f $(OBJ)
	@make -C libft clean
	@echo "$(YELLOW)[MINISHELL] $(RED).o deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "$(YELLOW)[MINISHELL] $(RED).a deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re debug