# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brandebr <brandebr@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 14:16:18 by brandebr          #+#    #+#              #
#    Updated: 2024/05/31 18:03:04 by brandebr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INC_DIR	= include/
SRC_DIR = src/

SRC = main.c print_utils.c error_parsing.c dinner_prep.c mutex_handle.c dinner_ending.c\
		dinner_starting.c setters_getters.c waiter.c sync_utils.c threading.c 

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

CC = gcc -g -lpthread -fsanitize=thread 
TEST_LEAKS	:= leaks -atExit --
TEST_ARGS ?= argv

VALGRIND = valgrind -s
VIKING =  valgrind  --leak-check=full
RAGNAROK = valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes 

FLAGS = -Wall -Wextra -Werror

all: Makefile $(NAME)

tleaks: all
	@$(TEST_LEAKS) ./$(NAME) 5 800 200 200 5

valgrind: all
	@$(VALGRIND) ./$(NAME) 5 1800 200 200 5

viking: all 
	@$(VIKING) ./$(NAME) 5 800 200 200 5

ragnarok: all
	@$(RAGNAROK) ./$(NAME) 5 800 200 200 5

%.o: %.c Makefile
	$(CC) -I $(INC_DIR) -c $< -o $@ $(FLAGS) 

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
 
clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re tleaks valgrind viking ragnarok