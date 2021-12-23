# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrochet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/23 13:01:56 by mrochet           #+#    #+#              #
#    Updated: 2021/12/23 14:42:02 by mrochet          ###   ########lyon.fr    #
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

PARS_NAME = analyse_file.c analyse_map.c parse_fcr.c parsing.c print_struct.c
SRCS_PARS	= $(addprefix parsing/, $(PARS_NAME))

UTILS_NAME = ft_free_split.c structure.c
SRCS_UTILS	= $(addprefix utils/, $(UTILS_NAME))

SRCS_NAME =	main.c $(SRCS_PARS) $(SRCS_UTILS)
SRCS_PATH = src/

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))

HEADER	= includes/cub3d.h

OBJ_PATH	= obj/
OBJ_NAME	= ${SRCS_NAME:.c=.o}
	OBJ			= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

RM		=	rm -rf
CC		=	gcc
#FSAN	=	-g -fsanitize=address
#CFLAGS	=	-Wall -Werror -Wextra

#FLAGS_MLX	= -l mlx -framework OpenGL -framework AppKit -L mlx -O3 -I minilibx
#LIB_X		= mlx/libmlx.a
LIB_FT		= libft/libft.a

$(OBJ_PATH)%.o:	$(SRCS_PATH)%.c includes/cub3d.h
	echo "$(BLUE)\n\t\tCUB3D :\n"
	mkdir -p obj/
	mkdir -p obj/parsing/
	mkdir -p obj/utils/
	printf "\033[2K\r$(LIGHT_PINK)Compiling:	\033[37m$<\033[36m \033[0m"
	${CC} ${CFLAGS} -I includes -c $< -o $@

all:	librairies
	$(MAKE) $(NAME)

$(NAME): ${OBJ} 
	$(CC) ${CFLAGS} -o ${NAME} ${OBJ} ${FLAGS_MLX} libft/*.o
librairies:
	make -C mlx
	make -C libft

clean:
	${RM} ${OBJ_PATH}
	echo "\t\t$(ORANGE)[Delete objs cub3d done]\n"
	make clean -C libft

fclean:
	${RM} ${OBJ_PATH}
	${RM} ${NAME}
	echo "\t\t$(ORANGE)[Delete objs cub3d done]\n"
	make fclean -C libft

clean_mlx:
	make clean -C mlx
	echo "\t\t$(ORANGE)[Delete objs MLX done]\n"

re:				fclean all

norme:
	/usr/bin/norminette $(SRCS_PATH)
