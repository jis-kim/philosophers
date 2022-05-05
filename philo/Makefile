# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiskim <jiskim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 20:09:20 by jiskim            #+#    #+#              #
#    Updated: 2022/05/06 04:43:20 by jiskim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC		=	gcc
RM		=	rm -rf
INCS_DIR	=	-I./includes

SRCS_DIR 		= ./srcs/
SRCS		= $(addprefix $(SRCS_DIR), \
				main.c \
				print_error.c \
				utils.c \
				initialize.c \
				philo_action.c \
				check_dead.c \
				)
OBJS 		= $(SRCS:.c=.o)

ifdef DEBUG
	CFLAGS = -g3 -fsanitize=address
else
	CFLAGS = -Wall -Wextra -Werror
endif

ifdef THREAD
	CFLAGS = -fsanitize=thread -g3
endif

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS_DIR) -o $@ -c $<
	@echo $(CUT)$(BOLD)$(L_GREEN) Compiling with $(CFLAGS)...$(RESET)
	@echo $(CUT)$(L_CYAN) [$(notdir $^)] to [$(notdir $@)] $(RESET)
	@printf $(UP)$(UP)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@
	@printf $(CUT)$(CUT)
	@echo $(BOLD)$(L_PURPLE) 🍝philosophers are ready to eat!!😋$(RESET)

clean:
	@$(RM) $(OBJS)
	@echo $(BOLD)$(YELLOW) Remove object files...💫$(RESET)

fclean: clean
	@$(RM) $(NAME)
	@echo $(BOLD)$(YELLOW) Bye philosophers...💫$(RESET)

re: fclean all

debug : fclean
	@make DEBUG=1

thread : fclean
	@make THREAD=1

.PHONY: all clean fclean re debug

######################### Color #########################
GREEN="\033[32m"
L_GREEN="\033[1;32m"
YELLOW="\033[33m"
RED="\033[31m"
L_RED="\033[1;31m"
BLUE="\033[34m"
L_BLUE="\033[1;34m"
MUTED="\033[130m"
RESET="\033[0m"
BOLD="\033[1m"
L_PURPLE="\033[1;35m"
L_CYAN="\033[1;36m"
L_GRAY="\033[1;37m"
L_WHITE="\033[1;38m"
L_YELLOW="\033[1;93m"
UP = "\033[A"
DOWN = "\033[B"
RIGHT = "\033[C"
LEFT = "\033[D"
CUT = "\033[K"
SAVE = "\033[s"
RESTORE = "\033[u"
