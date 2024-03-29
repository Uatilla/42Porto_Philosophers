# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arepsa <arepsa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 11:06:34 by arepsa            #+#    #+#              #
#    Updated: 2024/03/13 19:59:06 by uviana-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------ COLORS ------------ #
RESET	= \033[0m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

# ----------- COMMANDS ------------ #
CC = cc
RM = rm -rf

# ------------- FLAGS ------------- #
CFLAGS 	= -Wall -Wextra -Werror -g
TH_FLAG = -pthread #-fsanitize=thread
MK_FLAG = --no-print-directory

# -------------- PATHS -------------- #
INC			= includes
SRC_DIR		= srcs
OBJ_DIR		= objs

# /------------- FILES ------------- #
NAME 		= philo
FILES 		= main utils init_check prog_init action action_aux \
				printer monitor clean time utils_mtx debug_prints
SRC 		= $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJ 		= $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

# -------------- RULES --------------- #
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(TH_FLAG) $(OBJ) -o $(NAME) -I $(INC)
	echo "[$(GREEN)$(NAME) created$(RESET)]"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(OBJ_DIR):
	mkdir -p $@
	echo "[$(GREEN)objs directory created$(RESET)]"

clean:
	$(RM) $(OBJ_DIR)
	echo "[$(RED)objs removed$(RESET)]"

fclean: clean
	$(RM) $(NAME)
	echo "[$(RED)executable removed$(RESET)]"

re: fclean all


.PHONY: all clean fclean re
.SILENT:
