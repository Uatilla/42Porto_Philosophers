# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/23 18:57:07 by uviana-a          #+#    #+#              #
#    Updated: 2024/03/10 18:56:21 by uviana-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

# Colors
RESET 		=	\033[0m	
BLACK 		=	\033[1;30m
RED 		=	\033[1;31m
GREEN 		=	\033[1;32m
YELLOW 		=	\033[1;33m
BLUE 		=	\033[1;34m
PURPLE 		=	\033[1;35m
CYAN 		=	\033[1;36m
WHITE 		=	\033[1;37m

NAME		=	philo

# Commands
CC			= cc
RM			= rm -rf

# Diretories
SRCS_DIR	=	srcs
OBJS_DIR	=	objs
INCLUDES	=	includes


# Flags
CFLAGS		= -Wall -Wextra -Werror -g -O0
THFLAG		= -pthread #-fsanitize=thread
MK_FLAG		= --no-print-directory

# Files
SRCS		=	main.c input_validation.c exit.c utils.c
OBJS		=	$(SRCS:%.c=$(OBJS_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(THFLAG) $(OBJS) -o $(NAME)
	printf "Compiling		$(GREEN)[OK]$(RESET)\n"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	printf "Making binary files	$(YELLOW)[OK]$(RESET)\n"
	mkdir -p $(@D)
	$(CC) -I $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)
	printf "clean object files	$(CYAN)[OK]$(RESET)\n"

fclean: clean
	$(RM) $(NAME)
	printf "cleaning all files	$(CYAN)[OK]$(RESET)\n"
	
re: fclean all

.PHONY: all clean fclean re
