# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oubelhaj <oubelhaj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 18:40:00 by oubelhaj          #+#    #+#              #
#    Updated: 2023/07/05 16:09:19 by oubelhaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c file_opening.c lexer.c parser.c initialization.c error_handling.c expansion.c \
	 here_doc.c ./helpers/ft_atoi.c ./helpers/ft_is_whitespace.c ./helpers/ft_isalnum.c \
	./helpers/ft_isalpha.c ./helpers/ft_isdigit.c ./helpers/ft_putchar_fd.c ./helpers/ft_putnbr_fd.c \
	./helpers/ft_putstr_fd.c ./helpers/ft_exit_error.c ./helpers/ft_putendl.c ./linked_lists/ft_lstadd_back.c \
	./linked_lists/ft_lstclear.c ./linked_lists/ft_lstdelone.c ./linked_lists/ft_lstlast.c \
	./linked_lists/ft_lstnew.c ./linked_lists/ft_lstsize.c ./string_helpers/ft_free_strs.c \
	./string_helpers/ft_split.c ./string_helpers/ft_strdup.c ./string_helpers/ft_strjoin.c \
	./string_helpers/ft_strlen.c ./string_helpers/ft_strstr.c ./string_helpers/ft_strnstr.c \
	./string_helpers/ft_strncmp.c ./string_helpers/ft_strcmp.c ./string_helpers/ft_substr.c \
	./string_helpers/ft_strchr.c ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
	./linked_lists/ft_lstadd_back_alt.c ./linked_lists/ft_lstnew_alt.c ./linked_lists/ft_lstlast_alt.c

OBJS = ${SRC:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

.c.o	:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
	@echo "\033[1;32m- minishell compiled!\033[0m"

clean :
	@rm -rf *.o
	@rm -rf helpers/*.o
	@rm -rf linked_lists/*.o
	@rm -rf get_next_line/*.o
	@rm -rf string_helpers/*.o
	@echo "\033[1;33m- Object files removed!\033[0m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[1;31m- minishell deleted!\033[0m"

re : fclean all