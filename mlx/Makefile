#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11

COLOR_NONE=\033[0;0m
COLOR_RED=\033[1;31m
COLOR_GREEN=\033[1;32m
COLOR_YELLOW=\033[1;33m
COLOR_PINK=\033[1;35m
COLOR_CYAN=\033[1;36m

PREFIX=$(COLOR_YELLOW)[MLX]$(COLOR_NONE)  

all: $(NOM)

$(NOM):	$(OBJ)
	@ar -r $(NOM) $(OBJ)
	@ranlib $(NOM)
	@echo "$(PREFIX)$(COLOR_GREEN)$(NOM) generado!$(COLOR_NONE)"

clean:
	@rm -f $(OBJ) *~
	@echo "$(PREFIX)$(COLOR_RED)Objetos eliminados!$(COLOR_NONE)"

fclean: clean
	@rm -f $(NOM)
	@echo "$(PREFIX)$(COLOR_RED)$(NOM) eliminado!$(COLOR_NONE)"

re: fclean all

.PHONY: all clean fclean re