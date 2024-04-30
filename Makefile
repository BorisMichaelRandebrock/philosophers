# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 14:16:18 by brandebr          #+#    #+#              #
#    Updated: 2024/04/30 16:35:40 by brandebr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MAKEFLAGS 		+= --silent
NAME = philosophers

INC_DIR	= include/
SRC_DIR = src/

SRC = main.c utils.c error_parsing.c dinner_prep.c mutex_handle.c dinner_ending.c\
		dinner_starting.c

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

CC = gcc
TEST_LEAKS		:= leaks -atExit --
TEST_ARGS ?= argv

VALGRIND = valgrind -s
VIKING =  valgrind  --leak-check=full
RAGNAROK = valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes 

FLAGS = -Wall -Wextra -Werror
GREEN		:=\033[0;32m
RED		:=\033[0;31m
BLUE		:=\033[0;34m
RES		:=\033[0m

all: Makefile $(NAME)

tleaks: all
	@$(TEST_LEAKS) ./$(NAME) 5 800 200 200 5
# @$(TEST_LEAKS)./$(NAME) $(TEST_ARGS)

valgrind: all
	@$(VALGRIND) ./$(NAME) 5 800 200 200 5

viking: all
	@$(VIKING) ./$(NAME) 5 800 200 200 5

ragnarok: all
	@$(RAGNAROK) ./$(NAME) 5 800 200 200 5

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
