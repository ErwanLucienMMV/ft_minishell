# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/21 13:32:07 by abarthes          #+#    #+#              #
#    Updated: 2026/01/31 13:13:17 by abarthes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m
MAKEFLAGS += --no-print-directory
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

SRC =	terminal/terminal.c parser/tokenize.c parser/sanitize.c buildins/buildins.c \
		envpath/envpath.c envpath/envp_utils.c parser/utils.c expand/expand.c \
		signals/signals.c files_handler/fhandler.c

OBJ = $(SRC:.c=.o)

NAME = minishell
LIBFT= libft/libft.a

all: $(NAME) $(LIBFT)

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
