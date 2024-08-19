/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:45:05 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/19 17:42:04 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum			e_errors
{
	ERR_ARGS,
	ERR_FILE,
	ERR_READ,
	ERR_MALLOC,
	ERR_MAP,
	ERR_WIN,
	ERR_IMG,
	ERR_MLX
};

enum			e_exits
{
	EXIT_DEFEAT,
	EXIT_GOAL,
	EXIT_QUIT
};

# define TILE_EMPTY '0'
# define TILE_WALL '1'
# define TILE_COIN 'C'
# define TILE_GOAL 'E'
# define TILE_SPAWN 'P'
# define TILE_SPIKE 'S'
# define TILE_MIMIC 'M'

typedef struct s_map
{
	char		*map;
	char		*revealed;
	size_t		cols;
	size_t		rows;
	size_t		spawn;
	size_t		goal;
	size_t		coins;
}				t_map;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			cols;
	int			endian;
}				t_img;

typedef struct s_sprite
{
	t_img		img_data;
	int			width;
	int			height;
}				t_sprite;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_player
{
	int			pos;
	int			dir;
	int			move_count;
}				t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		win_img;
	t_point		size;
	int			scale;
}				t_mlx;

typedef struct s_data
{
	t_mlx		mlx_data;
	t_map		map_data;
	t_player	player_data;
	t_sprite	sprites[10];
}				t_data;

// exit_utils_bonus.c
void			error_exit(enum e_errors err);
void			game_exit(enum e_exits exit_code);

// read_map_bonus.c
char			*read_map(char *file);

// init_map_bonus.c
void			create_map(char *data, t_map *map);

// init_mlx_bonus.c
void			init_mlx(t_data *data);
void			create_img(t_img *img_data, void *mlx, int width, int height);
void			load_xpm_sprite(char *path, void *mlx, t_sprite *sprite);
void			create_win(t_data *data);
void			resize_win(int sign, t_data *data);

// point_utils_bonus.c
t_point			get_point(int x, int y);
t_point			add_points(t_point a, t_point b);
t_point			scale_point(t_point p, int s);

// draw_utils_bonus.c
unsigned int	*get_pixel_ptr(t_img *img, t_point pos);
void			draw_pixel(t_img *img, t_point pos, unsigned int color,
					int scale);
void			draw_sprite(t_sprite *spr, t_img *img, t_point pos, int scale);

// draw_scene_bonus.c
void			draw_scene(t_data *data);

// player_utils_bonus.c
int				move_player(int keycode, t_data *data);

#endif