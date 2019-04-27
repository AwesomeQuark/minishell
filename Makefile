# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: conoel <conoelstudent.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/10 21:14:13 by conoel            #+#    #+#              #
#    Updated: 2019/04/26 14:01:05 by conoel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell
AUTEUR =		"mbonati\nconoel"

SRC_NAME =		main.c\
				lexer.c\
				token_utils.c\
				exec_command.c\
				builtin.c\
				builtin2.c\
				utils.c\
				display.c

SRC_DIR =		./src/
SRC =			${addprefix $(SRC_DIR), $(SRC_NAME)}

OBJ_NAME =		$(SRC_NAME:.c=.o)
OBJ_DIR =		./obj/
OBJ =			${addprefix $(OBJ_DIR), $(OBJ_NAME)}

HEADER_DIR =	./include/
HEADER_NAME =	minishell.h\
				lexer.h
HEADER =		${addprefix $(HEADER_DIR), $(HEADER_NAME)}

LIB_NAME =		haflib.a
LIB_DIR =		./haflib/
LIB_HEADER =	./haflib/includes/
LIB =			${addprefix $(LIB_DIR), $(LIB_NAME)}

FLAGS =			-Wall -Werror -Wextra\
				-O0 -g3
CC =			clang

#################################################################################
##################################### RULES #####################################
#################################################################################

.PHONY: all clean fclean re
.SILENT:

##############################
########## GENERALS ##########
##############################

all: $(LIB) $(OBJ_DIR) $(NAME) $(HEADER)

re: fclean all

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIB_DIR)

fclean:
	make fclean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR) $(NAME) *.dSYM
	echo "\033[31m\033[1m\033[4mCleaning\033[0m\033[31m : Everything\033[0m [$(NAME)]";

###############################
######### COMPILATION #########
###############################

$(NAME): ./auteur $(OBJ_DIR) $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME) -I$(HEADER_DIR) -I$(LIB_DIR) `sdl2-config --cflags --libs`
	echo "\n \033[1m\033[4m\033[35m\\^/ Done compiling \\^/\033[0m [$(NAME)] --> $(LIB_NAME)"
	clear
	echo "#########################################################################"
	echo "##\033[32m  ___  ___   __   __  __   __    ___   __   __   ____   __     __    \033[0m##"
	echo "##\033[32m |   \/   | |  | |  \|  | |  | /  __| |  |_|  | | ___\ |  |   |  |   \033[0m##"
	echo "##\033[32m |  \__/  | |  | |      | |  | |__  | |   _   | | __|| |  |_  |  |_  \033[0m##"
	echo "##\033[32m |__|__|__| |__| |__|\__| |__| |____/ |__|_|__| |____/ |____| |____| \033[0m##"
	echo "##\033[32m |__|  |__| |__| |__|\__| |__| |____| |__| |__| |____| |____| |____| \033[0m##"
	echo "##                                                                     ##"
	echo "##################\033[32m MBONATI \033[0m####################\033[32m CONOEL \033[0m##################"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -I$(HEADER_DIR) -I$(LIB_HEADER) `sdl2-config --cflags`
	printf "\033[32m\033[1m\033[4mCompiling\033[0m\033[32m : %-30s \033[0m [$(NAME)]\n" $@


$(OBJ_DIR):
	clear
	mkdir $(OBJ_DIR)
	echo "\n>=========== * \033[32m\033[1mCreating $(NAME) obj dir\033[0m * ===========<";

./auteur:
	echo $(AUTEUR) > ./auteur
	echo "\033[32m<Created Author file>\033[0m"

###############################
############# LIB #############
###############################

$(LIB):
	make -C $(LIB_DIR)
