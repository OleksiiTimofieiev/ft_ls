# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 11:59:13 by otimofie          #+#    #+#              #
#    Updated: 2018/11/15 19:17:55 by otimofie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ls

CORE		=	main.c \
				main_infrastructure.c \
				main_infrastructure_2.c \
				quick_sort.c \
				time_quick_sort.c \
				list_infrastructure.c \
				list_infrastructure_2.c \
				list_infrastructure_3.c \
				listdir_infrastructure.c \
				stats_infrastructure.c \
				stats_infrastructure_2.c \
				flags.c \

SRCS        = $(addprefix srcs/, $(CORE))

CFLAGS		= -Wall -Wextra -Werror
OBJECTS 	= $(SRCS:.c=.o)
LIB			= ./libft.a
INC			= ./includes/ft_ls.h

#colors
RESET		= \033[m
RED         = \033[1;31m
GREEN       = \033[01;38;05;46m
YELLOW      = \033[01;38;05;226m
BLUE        = \033[03;38;05;21m
VIOLET      = \033[01;38;05;201m
CYAN        = \033[1;36m
WHITE       = \033[01;38;05;15m

all: $(NAME)

$(NAME): $(LIB) $(OBJECTS) $(INC)
	@ gcc $(CFLAGS) -I $(INC) $(SRCS) -L ./libft -lft -o $(NAME)
	@ echo  "$(YELLOW) : OK$(RESET)"

$(LIB):
	@ echo  "$(GREEN)Compiling: $(WHITE)libft$(RESET)$(YELLOW) : $(RESET)\c)"
	@ make -C ./libft
	@ echo  "$(GREEN)Compiling: $(WHITE)ft_ls$(RESET)$(YELLOW) : $(RESET)\c)"

$(OBJECTS): %.o: %.c
	@ gcc -c $(CFLAGS) $< -o $@
	@ echo  "$(YELLOW)█$(RESET)\c)"

clean:
	@ make -C ./libft clean
	@ rm -f $(OBJECTS)

fclean: clean
	@ make -C ./libft fclean
	@ rm -f $(NAME) $(LIB)

re: fclean all

.PHONY: all clean fclean re
