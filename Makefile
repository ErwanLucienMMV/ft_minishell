# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 13:32:07 by abarthes          #+#    #+#              #
#    Updated: 2026/03/08 01:09:10 by abarthes         ###   ########.fr        #
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
READLINE_PREFIX := $(shell command -v brew >/dev/null 2>&1 && brew --prefix readline 2>/dev/null || true)

ifeq ($(strip $(READLINE_PREFIX)),)
	READLINE_INCLUDES :=
	ifeq ($(shell uname -s),Darwin)
		READLINE_LIBS := -lreadline -lcurses
	else
		READLINE_LIBS := -lreadline -lncurses
	endif
else
	READLINE_INCLUDES := -I$(READLINE_PREFIX)/include
	ifeq ($(shell uname -s),Darwin)
		READLINE_LIBS := -L$(READLINE_PREFIX)/lib -lreadline -lcurses
	else
		READLINE_LIBS := -L$(READLINE_PREFIX)/lib -lreadline -lncurses
	endif
endif

SRC =	terminal/terminal.c parser/tokenize.c parser/sanitize.c \
		parser/sanitize_debug.c \
		parser/sanitize_individual_token.c parser/parser_check_its_quotes.c \
		parser/parser_check_its.c parser/parser_check_its_utils.c \
		parser/parser_list_operations.c parser/parser_list_utils.c \
		parser/utils_get_prev_next.c \
		buildins/buildins.c \
		buildins/buildin_exit.c buildins/utils_exit.c \
		buildins/buildin_envpath.c \
		buildins/buildin_unset_export.c buildins/buildin_cd.c \
		envpath/envpath.c envpath/envp_utils.c parser/utils.c \
		envpath/envp_operations.c \
		envpath/free_utils.c \
		expand/expand.c expand/expand_plain_text.c expand/expand_d_quote.c \
		expand/expand_d_quote_utils.c expand/expand_s_quotes.c \
		expand/nodes_operations.c \
		expand/checks_for_expand.c expand/checks_for_expand_utils.c \
		expand/calculate_env_size.c \
		expand/add_empty_nodes_to_their_next.c expand/add_empty_nodes_utils.c \
		expand/expand_env_var.c \
		expand/expand_plain_text_utils.c \
		signals/signals.c files_handler/fhandler.c here_doc/here_doc.c \
		here_doc/here_doc_expand.c here_doc/here_doc_signal.c \
		expand/node_merge_quoted.c here_doc/here_doc_utils.c \
		execve/execve.c execve/utils.c execve/utils_helpers.c \
		execve/find_command.c \
		execve/execve_piped.c execve/execve_debug.c \
		execve/parse_command.c execve/execve_checks.c \
		execve/execve_children.c execve/execve_exit_piped.c \
		execve/free_our_stuff.c execve/execve_piped_redirections.c \
		execve/execve_piped_redirections_utils.c execve/free_structures.c \
		execve/parse_commands_helper.c \
		execve/parse_commands_files.c execve/execve_without_pipe.c \
		execve/execve_no_pipes_redirections.c \
		execve/utils2.c \
		terminal/terminal_debug.c terminal/terminal_utils_handlers.c \
		buildins/buildin_echo.c \
		terminal/terminal_checks.c \
		errors/error.c errors/error2.c expand/utils.c \

OBJ = $(SRC:.c=.o)

NAME = minishell
LIBFT= libft/libft.a

all: $(NAME) $(LIBFT)

debug: CFLAGS += -g -D IS_DEBUG=1

debug: re

$(NAME): $(OBJ) $(LIBFT)
	@printf "$(YELLOW)[MINISHELL] $(GREEN).o created$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) \
	-Llibft -lft $(READLINE_LIBS) \
	-o $(NAME)
	@printf "$(YELLOW)[MINISHELL] $(GREEN)executable created$(RESET)\n"

%.o: %.c
	@$(CC) $(CFLAGS) $(READLINE_INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C libft

clean:
	@rm -f $(OBJ)
	@make -C libft clean
	@printf "$(YELLOW)[MINISHELL] $(RED).o deleted$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@printf "$(YELLOW)[MINISHELL] $(RED).a deleted$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re debug