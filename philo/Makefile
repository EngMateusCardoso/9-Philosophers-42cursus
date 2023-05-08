# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 19:25:05 by matcardo          #+#    #+#              #
#    Updated: 2023/05/07 23:09:09 by matcardo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

SRCS			= $(wildcard src/*.c)
OBJS			= ${SRCS:src/%.c=objs/%.o}
HEADER			= src/philo.h
OBJS_DIR		= objs/

RM				= rm -fr
CC				= gcc
FLAGS			= -Wall -Wextra -Werror -pthread

LEAKS 			= valgrind --tool=drd

GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
			@printf "\n$(CY)Generating philo executable...$(RC)\n"
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)
			@printf "$(GR)Done!$(RC)\n\n"

$(OBJS_DIR):
			mkdir $(OBJS_DIR)

objs/%.o: src/%.c
			@printf "\n$(CY)Generating object...$(RC)\n"
			${CC} ${FLAGS} -c $< -o ${<:src/%.c=objs/%.o}
			@printf "$(GR)Object ready!$(RC)"

norm:
			norminette ${SRCS} ${HEADER}

leaks:		$(NAME)
	$(LEAKS) ./$(NAME) 3 600 150 150 2
	
clean:
			$(RM) $(OBJS_DIR)
			@printf "$(RE)philo objects removed!$(RC)\n\n"

fclean:		clean
			$(RM) $(NAME)
			@printf "$(RE)philo executables removed!$(RC)\n\n"

re:			fclean all

.PHONY:		all clean fclean re
