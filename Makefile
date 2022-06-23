# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrochet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/23 13:01:56 by mrochet           #+#    #+#              #
#    Updated: 2022/05/30 20:02:04 by mrochet          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

BLUE =\033[0;38;5;123m
LIGHT_PINK = \033[0;38;5;200m
PINK = \033[0;38;5;198m
DARK_BLUE = \033[1;38;5;110m
GREEN = \033[1;32;111m
LIGHT_GREEN = \033[0;38;5;121m
LIGHT_RED = \033[0;31;5;110m
FLASH_GREEN = \033[33;32m
WHITE_BOLD = \033[37m
GREY = \033[3;90m
ORANGE = \033[3;91m
YELLOW = \033[0;33m

NAME = cub3d

PARS_NAME = parsing.c parsing_color.c parsing_file.c \
			print_struct.c utils_deux.c parsing_map.c
EXEC_NAME = raycaster.c utils.c draw.c run.c

SRCS_NAME =	main.c $(PARS_NAME) $(UTILS_NAME) $(EXEC_NAME)
SRCS_PATH = src/

#SRCS_PARS	= $(addprefix parsing/, $(PARS_NAME))
#SRCS_UTILS	= $(addprefix utils/, $(UTILS_NAME))
#SRCS_EXEC	= $(addprefix execution/, $(EXEC_NAME))
#SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))

HEADER	= includes/cub3d.h

OBJ_PATH	= obj/
OBJ_NAME	= $(SRCS_NAME:.c=.o)
OBJ			= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

RM		=	rm -rf
CC		=	gcc
#FSAN	=	-g -fsanitize=address
#CFLAGS	=	-Wall -Werror -Wextra

FLAGS_MLX	= -framework OpenGL -framework AppKit -O3
LIB_X		= mlx/libmlx.a
LIB_FT		= libft/libft.a

$(OBJ_PATH)%.o:	$(SRCS_PATH)%.c includes/cub3d.h
				$(CC) $(CFLAGS) -I includes -I libft -I mlx -c $< -o $@


all:			$(OBJ_PATH) $(NAME)
					@:

$(OBJ_PATH):
				mkdir -p obj/
			#	mkdir -p obj/parsing/
			#	mkdir -p obj/utils/
			#	mkdir -p obj/execution/

$(NAME):		$(OBJ) librairies
				$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB_FT) $(LIB_X) $(FLAGS_MLX)
				@echo "Compilation Succes !"

librairies:
				make -C mlx
				make -C libft

clean:
				${RM} $(OBJ_PATH)
				echo "\t\t$(ORANGE)[Delete objs cub3d done]\n"
				make clean -C libft
				@echo "Clean Succes !"

fclean:
				$(RM) $(OBJ_PATH)
				$(RM) $(NAME)
				make fclean -C libft

clean_mlx:
				make clean -C mlx

re:				fclean all

norme:
				/usr/bin/norminette $(SRCS_PATH)
