# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 14:16:18 by brandebr          #+#    #+#              #
#    Updated: 2024/04/25 19:13:36 by brandebr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS 		+= --silent
NAME = philosophers

INC_DIR	= include/
SRC_DIR = src/

SRC = main.c utils.c 

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

CC = gcc
TEST_LEAKS		:= leaks -atExit --
TEST_ARGS ?= argv

FLAGS = -Wall -Wextra -Werror -g
GREEN		:=\033[0;32m
RED		:=\033[0;31m
BLUE		:=\033[0;34m
RES		:=\033[0m

all: Makefile $(NAME)

tleaks: all
	@$(TEST_LEAKS) ./$(NAME) 5 800 200 200 200 7
# @$(TEST_LEAKS)./$(NAME) $(TEST_ARGS)

%.o: %.c
	@$(CC) -I $(INC_DIR) -c $< -o $@ $(FLAGS)
# @$(CC) -I $(INC_DIR) -c $< -o $@ $(FLAGS) $< -o $(OBJ_DIR)$@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re	
