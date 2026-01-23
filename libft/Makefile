# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthes <abarthes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/11 14:50:09 by abarthes          #+#    #+#              #
#    Updated: 2025/12/28 15:09:35 by abarthes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m
MAKEFLAGS += --silent
CC=cc
CFLAGS= -Wall -Wextra -Werror -g
SRC= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c \
get_next_line_utils.c ft_putstrings.c ft_printf.c ft_print_params.c ft_lstnew.c \
ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJ=$(SRC:.c=.o)
NAME= libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BLUE)[LIBFT] $(GREEN).o created $(RESET)"
	@ar rcs $(NAME) $(OBJ)
	@echo "$(BLUE)[LIBFT] $(GREEN).a created$(RESET)"

.o: .c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ)
	@echo "$(BLUE)[LIBFT] $(RED).o deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)[LIBFT] $(RED).a deleted$(RESET)"

re: fclean $(NAME)

.PHONY: all clean fclean re
