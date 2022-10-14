# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgross <dgross@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/07 17:25:15 by dgross            #+#    #+#              #
#    Updated: 2022/10/14 11:39:50 by dgross           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

LIBFT		= libft/libft.a

SRC			= pipex.c

OBJ_DIR		= ./obj/

OBJ			= $(addprefix $(OBJ_DIR),$(SRC:.c=.o))

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

INCLUDES	= -I./includes -I./libft/includes

LINCLUDES	= -L./libft -lft

g			= \033[1;32m
de 			= \033[0m
r 			= \033[0;31m
w			= \033[1;97m

all: $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

obj/%.o: src/%.c
	@echo "$(g)Compiling  $(w)$<$(de)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

--pipex_img:									 
	@echo "                                      $(g)⡠⢀⠄⠐⠒⢀⠠⠉⢉⠉⡉⢉⠉⡁⠤⠒⠢⢄⡀$(de)"
	@echo "                                    $(g)⢰⡁⢊⠀⠄⡈⠐⡀⠂⠌⡀⢂⠐⡀⢂⠐⠠⠁⡌⠠⢙⡷⢰⡄$(de)"
	@echo "                                    $(g)⢸⠽⣖⣭⠒⡤⢁⠠⣁⠢⠴⠤⠦⠴⠀⡈⠒⠁⠘⠁⡁⠠⢠⡇$(de)"
	@echo "██████╗ ██╗██████╗ ███████╗██╗  ██  $(g)⢸⡙⢦⢎⡱⢀⠂⡐⢀⠂⡐⢀⠂⡐⠠⢀⠡⠈⠄⠡⢀⠡⠀⡇$(de)"
	@echo "██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝ $(g)⠘⠹⣎⢮⡑⠄⢂⠰⢀⠂⡐⢀⠂⠄⡁⠂⠄⠡⢈⠐⣀⣢⡴⠁$(de)"
	@echo "██████╔╝██║██████╔╝█████╗   ╚███╔╝    $(g)⡿⣻⢿⣾⣶⣶⣶⣶⣴⣤⣬⣴⣴⡷⠾⠶⠶⠛⠋⢹$(de)"
	@echo "██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗    $(g)⡳⢭⣞⡱⢏⠚⡉⢉⠉⡉⠄⠠⠀⠄⡐⠠⠐⠠⢁⠸$(de)"
	@echo "██║     ██║██║     ███████╗██╔╝ ██╗   $(g)⣛⢖⢮⡑⠄⢂⠐⡀⢂⠐⡈⠄⡁⠂⠄⠡⢈⠐⠠⢸$(de)"
	@echo "╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝   $(g)⣏⢮⢳⢌⠂⠌⡐⢀⠂⡐⢀⠂⠄⠡⢈⠐⠠⢈⠐⢨$(de)"
	@echo "                                      $(g)⣞⠮⣝⢢⠁⢂⡐⠄⢂⠐⠠⠈⠄⡁⠂⠌⡐⠠⢈⠘$(de)"
	@echo "                                      $(g)⠫⣟⢮⠣⢌⠠⠐⡈⠄⡈⠄⡁⠂⠄⡁⢂⡐⣀⣂⡶⠁$(de)"
	@echo "                                       $(g)⠈⠉⠑⠈⠀⠐⠐⠒⠒⠀⠑⠀⠑⠚⠉⠉⠁$(de)"

$(NAME): --pipex_img obj $(OBJ)
	@$(MAKE) -C ./libft
	@$(CC) $(OBJ) $(CFLAGS) $(INCLUDES) $(LIBFT) $(LINCLUDES) -o $(NAME)
	@echo "$(g)Compiling Done ✔️$(de)"

clean:
	@echo "$(r)Cleaning 🧹 $(w)...$(de)"
	@$(MAKE) clean -C libft/
	@rm -rf obj

fclean: clean
	@$(MAKE) fclean -C libft/
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(INCLUDES)