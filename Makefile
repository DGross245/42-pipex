# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgross <dgross@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/07 17:25:15 by dgross            #+#    #+#              #
#    Updated: 2024/05/17 23:29:23 by dgross           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

BONUS_NAME	= pipex_bonus

LIBFT		= libft/libft.a

SRC			= main.c child.c error.c pipe.c

SRC_BONUS	= main_bonus.c child_bonus.c error_bonus.c here_doc_bonus.c pipe_bonus.c

OBJ_DIR		= ./obj/

B_OBJ_DIR	= ./bonus_obj/

OBJ			= $(addprefix $(OBJ_DIR),$(SRC:.c=.o))

B_OBJ		= $(addprefix $(B_OBJ_DIR),$(SRC_BONUS:.c=.o))

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

INCLUDES	= -I./includes -I./libft/includes

LINCLUDES	= -L./libft -lft

ge			= \033[1;33m
g			= \033[1;32m
de 			= \033[0m
r 			= \033[0;31m
w			= \033[1;97m

all: $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
	
b_obj:
	@mkdir -p $(B_OBJ_DIR)

obj/%.o: src/%.c
	@echo "$(g)Compiling  $(w)$<$(de)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
bonus_obj/%.o: bonus/%.c
	@echo "$(ge)Compiling  $(w)$<$(de)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

--pipex_img:
	@echo "                                   "
	@echo "                                   "
	@echo "                                   "
	@echo "██████╗ ██╗██████╗ ███████╗██╗  ██ "
	@echo "██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝"
	@echo "██████╔╝██║██████╔╝█████╗   ╚███╔╝ "
	@echo "██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ "
	@echo "██║     ██║██║     ███████╗██╔╝ ██╗"
	@echo "╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝"
	@echo "                                   "
	@echo "                                   "
	@echo "                                   "

$(NAME): --pipex_img obj $(OBJ)
	@$(MAKE) -C ./libft
	@$(CC) $(OBJ) $(CFLAGS) $(INCLUDES) $(LIBFT) $(LINCLUDES) -o $(NAME)
	@echo "$(g)Compiling Done ✔️$(de)"
	
bonus: --pipex_img b_obj $(B_OBJ)
	@$(MAKE) -C ./libft
	@$(CC) $(B_OBJ) $(CFLAGS) $(INCLUDES) $(LIBFT) $(LINCLUDES) -o $(BONUS_NAME)
	@echo "$(ge)Compiling Done ✔️$(de)"

clean:
	@echo "$(r)Cleaning 🧹 $(w)...$(de)"
	@$(MAKE) clean -C libft/
	@rm -rf obj
	@rm -rf bonus_obj

fclean: clean
	@$(MAKE) fclean -C libft/
	@rm -rf $(NAME)
	@rm -rf $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(INCLUDES)