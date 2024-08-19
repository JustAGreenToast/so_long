# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/05 13:54:06 by pfontenl          #+#    #+#              #
#    Updated: 2024/01/22 12:47:58 by pfontenl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

NAME=so_long
FILES=	draw_scene.c \
		draw_utils.c \
		exit_utils.c \
		init_map.c \
		init_mlx.c \
		mlx_utils.c \
		player_utils.c \
		point_utils.c \
		read_map.c \
		so_long.c
SRC=$(addprefix src/,$(FILES))
OBJ=$(addprefix obj/,$(FILES:.c=.o))
HEADER=src/so_long.h
INCLUDE=Makefile $(HEADER)

MLX=mlx
MLX_MAKE=make --no-print-directory -C $(MLX)

LIBFT=libft/libft.a
LIBFT_MAKE=make --no-print-directory -C libft/

NAME_BONUS=so_long_bonus
FILES_BONUS=draw_scene_bonus.c \
			draw_utils_bonus.c \
			exit_utils_bonus.c \
			init_map_bonus.c \
			init_mlx_bonus.c \
			mlx_utils_bonus.c \
			player_utils_bonus.c \
			point_utils_bonus.c \
			read_map_bonus.c \
			so_long_bonus.c
SRC_BONUS=$(addprefix src_bonus/,$(FILES_BONUS))
OBJ_BONUS=$(addprefix obj_bonus/,$(FILES_BONUS:.c=.o))
HEADER_BONUS=src_bonus/so_long_bonus.h
INCLUDE_BONUS=Makefile $(HEADER_BONUS)

CC=cc
CFLAGS=-Wall -Wextra -Werror -I $(MLX)
MLX_FLAGS=-L$(MLX) -lmlx -framework OpenGL -framework AppKit

COLOR_NONE=\033[0;0m
COLOR_RED=\033[1;31m
COLOR_GREEN=\033[1;32m
COLOR_YELLOW=\033[1;33m
COLOR_PINK=\033[1;35m
COLOR_CYAN=\033[1;36m

PREFIX=$(COLOR_YELLOW)[SO_LONG]$(COLOR_NONE)  
PREFIX_BONUS=$(COLOR_YELLOW)[SO_LONG]$(COLOR_NONE) $(COLOR_PINK)(BONUS)$(COLOR_NONE)  

all: $(NAME)

$(NAME): libft mlx $(OBJ)
	@$(CC) $(LIBFT) $(OBJ) $(MLX_FLAGS) -o $(NAME)
	@echo "$(PREFIX)$(COLOR_GREEN)$(NAME) generado!$(COLOR_NONE)"

obj/%.o: src/%.c $(INCLUDE)
	@mkdir -p obj/
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(PREFIX)$(COLOR_CYAN)Compilado $< a $@!$(COLOR_NONE)\n"

libft:
	@printf "$(PREFIX)$(COLOR_CYAN)Compilando libft...$(COLOR_NONE)\n"
	@$(LIBFT_MAKE)
	@printf "$(PREFIX)$(COLOR_GREEN)libft compilado!$(COLOR_NONE)\n"

mlx:
	@printf "$(PREFIX)$(COLOR_CYAN)Compilando MiniLibX...$(COLOR_NONE)\n"
	@$(MLX_MAKE)
	@printf "$(PREFIX)$(COLOR_GREEN)MiniLibX compilado!$(COLOR_NONE)\n"

bonus: $(NAME_BONUS)

$(NAME_BONUS): libft mlx $(OBJ_BONUS)
	@$(CC) $(LIBFT) $(OBJ_BONUS) $(MLX_FLAGS) -o $(NAME_BONUS)
	@echo "$(PREFIX_BONUS)$(COLOR_GREEN)$(NAME_BONUS) generado!$(COLOR_NONE)"

obj_bonus/%.o: src_bonus/%.c $(INCLUDE_BONUS)
	@mkdir -p obj_bonus/
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(PREFIX_BONUS)$(COLOR_CYAN)Compilado $< a $@!$(COLOR_NONE)\n"

clean:
	@$(LIBFT_MAKE) clean
	@$(MLX_MAKE) clean
	@rm -rf obj/ obj_bonus/
	@echo "$(PREFIX)$(COLOR_RED)Objetos eliminados!$(COLOR_NONE)"

fclean: clean
	@$(LIBFT_MAKE) fclean
	@$(MLX_MAKE) fclean
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@echo "$(PREFIX)$(COLOR_RED)$(NAME) eliminado!$(COLOR_NONE)"

re: fclean all

.PHONY: all libft mlx clean fclean re bonus