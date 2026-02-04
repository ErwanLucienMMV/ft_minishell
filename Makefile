# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 13:32:07 by abarthes          #+#    #+#              #
#    Updated: 2026/02/04 02:40:39 by emaigne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m
MAKEFLAGS += --no-print-directory
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

SRC =	terminal/terminal.c parser/tokenize.c parser/sanitize.c \
		parser/parser_check_its.c parser/parser_list_operations.c buildins/buildins.c \
		buildins/buildin_exit.c buildins/buildin_envpath.c \
		envpath/envpath.c envpath/envp_utils.c parser/utils.c \
		envpath/envp_operations.c \
		expand/expand.c expand/expand_plain_text.c expand/expand_d_quote.c \
		signals/signals.c files_handler/fhandler.c here_doc/here_doc.c \
		execve/execve.c execve/utils.c execve/find_command.c execve/execve_piped.c \
		execve/parse_command.c execve/execve_checks.c execve/execve_children.c \
		terminal/terminal_debug.c

OBJ = $(SRC:.c=.o)

NAME = minishell
LIBFT= libft/libft.a

all: $(NAME) $(LIBFT)

debug: CFLAGS += -D IS_DEBUG=1

debug: all

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(YELLOW)[MINISHELL] $(GREEN).o created $(RESET)"
	@$(CC) $(OBJ) \
	-Llibft -lft -lreadline \
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

.PHONY: all clean fclean re
